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
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  resp_begin_html (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_end_html () ; 

__attribute__((used)) static void
pg_error_internal(void)
{
	resp_begin_html(500, "Internal Server Error", NULL);
	puts("<p>Internal Server Error</p>");
	resp_end_html();
}