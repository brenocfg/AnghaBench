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

size_t sldns_b32_ntop_calculate_size(size_t src_data_length)
{
	return src_data_length == 0 ? 0 : ((src_data_length - 1) / 5 + 1) * 8;
}