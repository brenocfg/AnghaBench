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
struct line_number_mapping {int source_start; int destination_length; int source_length; int destination_start; } ;

/* Variables and functions */

__attribute__((used)) static int map_line_number(int line_number,
	const struct line_number_mapping *mapping)
{
	return ((line_number - mapping->source_start) * 2 + 1) *
	       mapping->destination_length /
	       (mapping->source_length * 2) +
	       mapping->destination_start;
}