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
struct oper_class_map {int bw; } ;

/* Variables and functions */
#define  BW160 134 
#define  BW20 133 
#define  BW2160 132 
#define  BW40MINUS 131 
#define  BW40PLUS 130 
#define  BW80 129 
#define  BW80P80 128 

int oper_class_bw_to_int(const struct oper_class_map *map)
{
	switch (map->bw) {
	case BW20:
		return 20;
	case BW40PLUS:
	case BW40MINUS:
		return 40;
	case BW80:
		return 80;
	case BW80P80:
	case BW160:
		return 160;
	case BW2160:
		return 2160;
	default:
		return 0;
	}
}