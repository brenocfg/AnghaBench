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
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krping_cdevsw ; 
 int /*<<< orphan*/  krping_dev ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
krping_loader(struct module *m, int what, void *arg)
{
	int err = 0;

	switch (what) {
	case MOD_LOAD:                /* kldload */
		krping_dev = make_dev(&krping_cdevsw, 0, UID_ROOT, GID_WHEEL,
					0600, "krping");
		printf("Krping device loaded.\n");
		break;
	case MOD_UNLOAD:
		destroy_dev(krping_dev);
		printf("Krping device unloaded.\n");
		break;
	default:
		err = EOPNOTSUPP;
		break;
	}

	return (err);
}