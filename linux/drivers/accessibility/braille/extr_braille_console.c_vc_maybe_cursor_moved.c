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
struct vc_data {scalar_t__ vc_x; scalar_t__ vc_y; } ;

/* Variables and functions */
 scalar_t__ lastvc_x ; 
 scalar_t__ lastvc_y ; 
 int /*<<< orphan*/  vc_follow_cursor (struct vc_data*) ; 

__attribute__((used)) static void vc_maybe_cursor_moved(struct vc_data *vc)
{
	if (vc->vc_x != lastvc_x || vc->vc_y != lastvc_y)
		vc_follow_cursor(vc);
}