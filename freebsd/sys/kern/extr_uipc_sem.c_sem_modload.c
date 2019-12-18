#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct module {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  ksem_count_lock ; 
 int ksem_dead ; 
 int /*<<< orphan*/  ksem_module_destroy () ; 
 int ksem_module_init () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsems ; 

__attribute__((used)) static int
sem_modload(struct module *module, int cmd, void *arg)
{
        int error = 0;

        switch (cmd) {
        case MOD_LOAD:
		error = ksem_module_init();
		if (error)
			ksem_module_destroy();
                break;

        case MOD_UNLOAD:
		mtx_lock(&ksem_count_lock);
		if (nsems != 0) {
			error = EOPNOTSUPP;
			mtx_unlock(&ksem_count_lock);
			break;
		}
		ksem_dead = 1;
		mtx_unlock(&ksem_count_lock);
		ksem_module_destroy();
                break;

        case MOD_SHUTDOWN:
                break;
        default:
                error = EINVAL;
                break;
        }
        return (error);
}