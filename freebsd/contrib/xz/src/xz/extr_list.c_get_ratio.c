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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,double const) ; 

__attribute__((used)) static const char *
get_ratio(uint64_t compressed_size, uint64_t uncompressed_size)
{
	if (uncompressed_size == 0)
		return "---";

	const double ratio = (double)(compressed_size)
			/ (double)(uncompressed_size);
	if (ratio > 9.999)
		return "---";

	static char buf[16];
	snprintf(buf, sizeof(buf), "%.3f", ratio);
	return buf;
}