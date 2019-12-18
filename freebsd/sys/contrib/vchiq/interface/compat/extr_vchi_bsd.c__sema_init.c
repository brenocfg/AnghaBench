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
struct semaphore {int value; int /*<<< orphan*/  cv; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int MTX_DEF ; 
 int MTX_NOWITNESS ; 
 int MTX_QUIET ; 
 int /*<<< orphan*/  bzero (struct semaphore*,int) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int) ; 

void
_sema_init(struct semaphore *s, int value)
{
	bzero(s, sizeof(*s));
	mtx_init(&s->mtx, "sema lock", "VCHIQ sepmaphore backing lock",
		MTX_DEF | MTX_NOWITNESS | MTX_QUIET);
	cv_init(&s->cv, "sema cv");
	s->value = value;
}