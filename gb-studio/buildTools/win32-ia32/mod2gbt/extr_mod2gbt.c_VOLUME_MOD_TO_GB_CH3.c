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

/* Variables and functions */
 int VOLUME_MOD_TO_GB (int) ; 

int VOLUME_MOD_TO_GB_CH3(int v) // channel 3
{
    int vol = VOLUME_MOD_TO_GB(v);
    switch(vol)
    {
        case 0: case 1: case 2: case 3: return 0;
        case 4: case 5: case 6: case 7: return 3;
        case 8: case 9: case 10: case 11: return 2;
        default:
        case 12: case 13: case 14: case 15: return 1;
    }

    return 0;
}