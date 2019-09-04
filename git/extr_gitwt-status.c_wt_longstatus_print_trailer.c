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
struct wt_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void wt_longstatus_print_trailer(struct wt_status *s)
{
	status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
}