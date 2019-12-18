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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int hw_changes_brightness ; 

__attribute__((used)) static int video_hw_changes_brightness(
	const struct dmi_system_id *d)
{
	if (hw_changes_brightness == -1)
		hw_changes_brightness = 1;
	return 0;
}