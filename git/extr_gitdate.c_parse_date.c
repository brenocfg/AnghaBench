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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  date_string (int /*<<< orphan*/ ,int,struct strbuf*) ; 
 scalar_t__ parse_date_basic (char const*,int /*<<< orphan*/ *,int*) ; 

int parse_date(const char *date, struct strbuf *result)
{
	timestamp_t timestamp;
	int offset;
	if (parse_date_basic(date, &timestamp, &offset))
		return -1;
	date_string(timestamp, offset, result);
	return 0;
}