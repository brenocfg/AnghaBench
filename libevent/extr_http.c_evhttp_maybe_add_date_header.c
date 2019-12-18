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
struct evkeyvalq {int dummy; } ;
typedef  int /*<<< orphan*/  date ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_add_header (struct evkeyvalq*,char*,char*) ; 
 int /*<<< orphan*/ * evhttp_find_header (struct evkeyvalq*,char*) ; 
 int evutil_date_rfc1123 (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evhttp_maybe_add_date_header(struct evkeyvalq *headers)
{
	if (evhttp_find_header(headers, "Date") == NULL) {
		char date[50];
		if (sizeof(date) - evutil_date_rfc1123(date, sizeof(date), NULL) > 0) {
			evhttp_add_header(headers, "Date", date);
		}
	}
}