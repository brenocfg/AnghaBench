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
typedef  int NCURSES_COLOR_T ;

/* Variables and functions */

__attribute__((used)) static void
rgb2hls(int r, int g, int b, NCURSES_COLOR_T *h, NCURSES_COLOR_T *l, NCURSES_COLOR_T *s)
/* convert RGB to HLS system */
{
    int min, max, t;

    if ((min = g < r ? g : r) > b)
	min = b;
    if ((max = g > r ? g : r) < b)
	max = b;

    /* calculate lightness */
    *l = (NCURSES_COLOR_T) ((min + max) / 20);

    if (min == max) {		/* black, white and all shades of gray */
	*h = 0;
	*s = 0;
	return;
    }

    /* calculate saturation */
    if (*l < 50)
	*s = (NCURSES_COLOR_T) (((max - min) * 100) / (max + min));
    else
	*s = (NCURSES_COLOR_T) (((max - min) * 100) / (2000 - max - min));

    /* calculate hue */
    if (r == max)
	t = (NCURSES_COLOR_T) (120 + ((g - b) * 60) / (max - min));
    else if (g == max)
	t = (NCURSES_COLOR_T) (240 + ((b - r) * 60) / (max - min));
    else
	t = (NCURSES_COLOR_T) (360 + ((r - g) * 60) / (max - min));

    *h = (NCURSES_COLOR_T) (t % 360);
}