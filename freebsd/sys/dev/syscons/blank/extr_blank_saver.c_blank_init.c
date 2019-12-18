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
typedef  int /*<<< orphan*/  video_adapter_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  V_DISPLAY_ON ; 
 scalar_t__ vidd_blank_display (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
blank_init(video_adapter_t *adp)
{
	if (vidd_blank_display(adp, V_DISPLAY_ON) == 0)
		return 0;
	return ENODEV;
}