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
struct TYPE_2__ {int fatLightmapCols; int fatLightmapRows; scalar_t__ worldDeluxeMapping; } ;

/* Variables and functions */
 TYPE_1__ tr ; 

__attribute__((used)) static float FatPackV(float input, int lightmapnum)
{
	if (lightmapnum < 0)
		return input;

	if (tr.worldDeluxeMapping)
		lightmapnum >>= 1;

	if (tr.fatLightmapCols > 0)
	{
		lightmapnum %= (tr.fatLightmapCols * tr.fatLightmapRows);
		return (input + (lightmapnum / tr.fatLightmapCols)) / (float)(tr.fatLightmapRows);
	}

	return input;
}