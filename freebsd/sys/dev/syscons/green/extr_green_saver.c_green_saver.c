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
 int /*<<< orphan*/  V_DISPLAY_ON ; 
 int /*<<< orphan*/  V_DISPLAY_STAND_BY ; 
 int /*<<< orphan*/  vidd_blank_display (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
green_saver(video_adapter_t *adp, int blank)
{
	vidd_blank_display(adp,
	    (blank) ? V_DISPLAY_STAND_BY : V_DISPLAY_ON);
	return 0;
}