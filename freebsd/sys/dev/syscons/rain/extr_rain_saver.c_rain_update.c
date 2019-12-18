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
 size_t BLUE (int) ; 
 int MAX ; 
 int* rain_pal ; 
 int /*<<< orphan*/  vidd_load_palette (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
rain_update(video_adapter_t *adp)
{
	int i, t;

	t = rain_pal[BLUE(MAX)];
	for (i = MAX; i > 1; i--)
		rain_pal[BLUE(i)] = rain_pal[BLUE(i - 1)];
	rain_pal[BLUE(1)] = t;
	vidd_load_palette(adp, rain_pal);
}