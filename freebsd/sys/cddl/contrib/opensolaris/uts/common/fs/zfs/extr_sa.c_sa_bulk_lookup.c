#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_1__ sa_handle_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_bulk_lookup_locked (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
sa_bulk_lookup(sa_handle_t *hdl, sa_bulk_attr_t *attrs, int count)
{
	int error;

	ASSERT(hdl);
	mutex_enter(&hdl->sa_lock);
	error = sa_bulk_lookup_locked(hdl, attrs, count);
	mutex_exit(&hdl->sa_lock);
	return (error);
}