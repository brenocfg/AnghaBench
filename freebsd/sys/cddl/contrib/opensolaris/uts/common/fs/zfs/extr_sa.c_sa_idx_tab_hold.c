#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa_lock; } ;
typedef  TYPE_1__ sa_os_t ;
struct TYPE_7__ {int /*<<< orphan*/  sa_refcount; } ;
typedef  TYPE_2__ sa_idx_tab_t ;
struct TYPE_8__ {TYPE_1__* os_sa; } ;
typedef  TYPE_3__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sa_idx_tab_hold(objset_t *os, sa_idx_tab_t *idx_tab)
{
	sa_os_t *sa = os->os_sa;

	ASSERT(MUTEX_HELD(&sa->sa_lock));
	(void) zfs_refcount_add(&idx_tab->sa_refcount, NULL);
}