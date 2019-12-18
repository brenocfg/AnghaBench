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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct evkeyvalq {int dummy; } ;
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_add_header (struct evkeyvalq*,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (struct evkeyvalq*,char*) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evhttp_maybe_add_date_header(struct evkeyvalq *headers)
{
	if (evhttp_find_header(headers, "Date") == NULL) {
		char date[50];
#ifndef _WIN32
		struct tm cur;
#endif
		struct tm *cur_p;
		time_t t = time(NULL);
#ifdef _WIN32
		cur_p = gmtime(&t);
#else
		gmtime_r(&t, &cur);
		cur_p = &cur;
#endif
		if (strftime(date, sizeof(date),
			"%a, %d %b %Y %H:%M:%S GMT", cur_p) != 0) {
			evhttp_add_header(headers, "Date", date);
		}
	}
}