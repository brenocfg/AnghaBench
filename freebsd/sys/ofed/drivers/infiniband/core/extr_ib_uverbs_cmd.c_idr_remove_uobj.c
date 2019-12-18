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
struct idr {int dummy; } ;
struct ib_uobject {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_uverbs_idr_lock ; 
 int /*<<< orphan*/  idr_remove (struct idr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void idr_remove_uobj(struct idr *idr, struct ib_uobject *uobj)
{
	spin_lock(&ib_uverbs_idr_lock);
	idr_remove(idr, uobj->id);
	spin_unlock(&ib_uverbs_idr_lock);
}