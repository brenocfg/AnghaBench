#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dmu_buf_t ;
struct TYPE_4__ {TYPE_1__* db_objset; } ;
typedef  TYPE_2__ dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/ * arc_loan_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

arc_buf_t *
dmu_request_arcbuf(dmu_buf_t *handle, int size)
{
	dmu_buf_impl_t *db = (dmu_buf_impl_t *)handle;

	return (arc_loan_buf(db->db_objset->os_spa, B_FALSE, size));
}