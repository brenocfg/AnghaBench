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
struct hhook_head {int hhh_refcount; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  HHHLIST_LOCK () ; 
 int /*<<< orphan*/  HHHLIST_UNLOCK () ; 
 int /*<<< orphan*/  hhook_head_destroy (struct hhook_head*) ; 

int
hhook_head_deregister(struct hhook_head *hhh)
{
	int error;

	error = 0;

	HHHLIST_LOCK();
	if (hhh == NULL)
		error = ENOENT;
	else if (hhh->hhh_refcount > 1)
		error = EBUSY;
	else
		hhook_head_destroy(hhh);
	HHHLIST_UNLOCK();

	return (error);
}