#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tunable ;
typedef  int /*<<< orphan*/  rgb ;
struct TYPE_2__ {unsigned char r; unsigned char g; unsigned char b; } ;

/* Variables and functions */
 int NCOLORS ; 
 scalar_t__ TUNABLE_STR_FETCH (char*,char*,int) ; 
 TYPE_1__* color_def ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ vt_parse_rgb_triplet (char*,unsigned char*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static void
vt_palette_init(void)
{
	int i;
	char rgb[32];
	char tunable[32];
	unsigned char r, g, b;

	for (i = 0; i < NCOLORS; i++) {
		snprintf(tunable, sizeof(tunable),
		    "kern.vt.color.%d.rgb", i);
		if (TUNABLE_STR_FETCH(tunable, rgb, sizeof(rgb))) {
			if (vt_parse_rgb_triplet(rgb, &r, &g, &b) == 0) {
				/* convert to percentages */
				color_def[i].r = r*100/255;
				color_def[i].g = g*100/255;
				color_def[i].b = b*100/255;
			}
		}
	}
}