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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int V_MODE_MAP_SIZE ; 
 int map_mode_num (int) ; 
 int /*<<< orphan*/ ** mode_map ; 

__attribute__((used)) static u_char 
*get_mode_param(int mode)
{
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
    if (mode >= V_MODE_MAP_SIZE)
	mode = map_mode_num(mode);
#endif
    if ((mode >= 0) && (mode < V_MODE_MAP_SIZE))
	return mode_map[mode];
    else
	return NULL;
}