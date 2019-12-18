#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_1__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_replace_all_by_template_locked (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
sa_replace_all_by_template(sa_handle_t *hdl, sa_bulk_attr_t *attr_desc,
    int attr_count, dmu_tx_t *tx)
{
	int error;

	mutex_enter(&hdl->sa_lock);
	error = sa_replace_all_by_template_locked(hdl, attr_desc,
	    attr_count, tx);
	mutex_exit(&hdl->sa_lock);
	return (error);
}