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
struct vpe_notifications {int /*<<< orphan*/  list; } ;
struct vpe {int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 struct vpe* get_vpe (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vpe_notify(int index, struct vpe_notifications *notify)
{
	struct vpe *v = get_vpe(index);

	if (v == NULL)
		return -1;

	list_add(&notify->list, &v->notify);
	return 0;
}