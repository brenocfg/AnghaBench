#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  stime; int /*<<< orphan*/  ttime; int /*<<< orphan*/  dynls; int /*<<< orphan*/  ebase; scalar_t__ this_tai; scalar_t__ next_tai; } ;
struct TYPE_8__ {TYPE_1__ head; } ;
typedef  TYPE_2__ leap_table_t ;
struct TYPE_9__ {int /*<<< orphan*/  dynamic; int /*<<< orphan*/  ttime; int /*<<< orphan*/  ebase; scalar_t__ tai_diff; scalar_t__ tai_offs; } ;
typedef  TYPE_3__ leap_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* leapsec_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ucmpv64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int/*BOOL*/
leapsec_frame(
        leap_result_t *qr)
{
	const leap_table_t * pt;

        memset(qr, 0, sizeof(leap_result_t));
	pt = leapsec_get_table(FALSE);

	qr->tai_offs = pt->head.this_tai;
	qr->tai_diff = pt->head.next_tai - pt->head.this_tai;
	qr->ebase    = pt->head.ebase;
	qr->ttime    = pt->head.ttime;
	qr->dynamic  = pt->head.dynls;

	return ucmpv64(&pt->head.ttime, &pt->head.stime) >= 0;
}