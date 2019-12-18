#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vint64 ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  expire; } ;
struct TYPE_5__ {TYPE_1__ head; } ;
typedef  TYPE_2__ leap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* leapsec_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntpcal_ntp_to_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ ucmpv64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int/*BOOL*/
leapsec_expired(
	uint32_t       when,
	const time_t * tpiv)
{
	const leap_table_t * pt;
	vint64 limit;

	pt = leapsec_get_table(FALSE);
	limit = ntpcal_ntp_to_ntp(when, tpiv);
	return ucmpv64(&limit, &pt->head.expire) >= 0;
}