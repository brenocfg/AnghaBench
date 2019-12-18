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
typedef  int /*<<< orphan*/  cnd_t ;

/* Variables and functions */
#define  ENOMEM 128 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int thrd_error ; 
 int thrd_nomem ; 
 int thrd_success ; 

int
cnd_init(cnd_t *cond)
{

	switch (pthread_cond_init(cond, NULL)) {
	case 0:
		return (thrd_success);
	case ENOMEM:
		return (thrd_nomem);
	default:
		return (thrd_error);
	}
}