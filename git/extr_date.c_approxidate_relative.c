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
typedef  int /*<<< orphan*/  timestamp_t ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  approxidate_str (char const*,struct timeval const*,int*) ; 
 int /*<<< orphan*/  get_time (struct timeval*) ; 
 int /*<<< orphan*/  parse_date_basic (char const*,int /*<<< orphan*/ *,int*) ; 

timestamp_t approxidate_relative(const char *date)
{
	struct timeval tv;
	timestamp_t timestamp;
	int offset;
	int errors = 0;

	if (!parse_date_basic(date, &timestamp, &offset))
		return timestamp;

	get_time(&tv);
	return approxidate_str(date, (const struct timeval *) &tv, &errors);
}