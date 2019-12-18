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
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ pcx_draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splash_mode ; 
 scalar_t__ splash_on ; 
 scalar_t__ vidd_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcx_splash(video_adapter_t *adp, int on)
{
	if (on) {
		if (!splash_on) {
			if (vidd_set_mode(adp, splash_mode) || pcx_draw(adp))
				return 1;
			splash_on = TRUE;
		}
		return (0);
	} else {
		splash_on = FALSE;
		return (0);
	}
}