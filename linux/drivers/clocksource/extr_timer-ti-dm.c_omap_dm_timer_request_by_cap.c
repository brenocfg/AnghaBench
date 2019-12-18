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
typedef  int /*<<< orphan*/  u32 ;
struct omap_dm_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_BY_CAP ; 
 struct omap_dm_timer* _omap_dm_timer_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct omap_dm_timer *omap_dm_timer_request_by_cap(u32 cap)
{
	return _omap_dm_timer_request(REQUEST_BY_CAP, &cap);
}