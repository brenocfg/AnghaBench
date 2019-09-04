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
typedef  int time_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  date_string (int,int,struct strbuf*) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 int /*<<< orphan*/  time (int*) ; 
 int tm_to_time_t (int /*<<< orphan*/ ) ; 

void datestamp(struct strbuf *out)
{
	time_t now;
	int offset;

	time(&now);

	offset = tm_to_time_t(localtime(&now)) - now;
	offset /= 60;

	date_string(now, offset, out);
}