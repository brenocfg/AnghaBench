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
struct pic {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pic*,int /*<<< orphan*/ ) ; 
 scalar_t__ intr_pic_registered (struct pic*) ; 
 int /*<<< orphan*/  intrpic_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pics ; 

int
intr_register_pic(struct pic *pic)
{
	int error;

	mtx_lock(&intrpic_lock);
	if (intr_pic_registered(pic))
		error = EBUSY;
	else {
		TAILQ_INSERT_TAIL(&pics, pic, pics);
		error = 0;
	}
	mtx_unlock(&intrpic_lock);
	return (error);
}