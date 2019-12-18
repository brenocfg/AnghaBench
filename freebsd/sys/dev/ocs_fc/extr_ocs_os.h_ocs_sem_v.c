#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ ocs_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ocs_sem_v(ocs_sem_t *sem)
{
	sema_post(&sem->sem);
}