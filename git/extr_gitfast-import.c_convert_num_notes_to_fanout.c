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
typedef  int uintmax_t ;

/* Variables and functions */

__attribute__((used)) static unsigned char convert_num_notes_to_fanout(uintmax_t num_notes)
{
	unsigned char fanout = 0;
	while ((num_notes >>= 8))
		fanout++;
	return fanout;
}