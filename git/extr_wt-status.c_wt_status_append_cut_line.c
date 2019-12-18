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
struct strbuf {int dummy; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  cut_line ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void wt_status_append_cut_line(struct strbuf *buf)
{
	const char *explanation = _("Do not modify or remove the line above.\nEverything below it will be ignored.");

	strbuf_commented_addf(buf, "%s", cut_line);
	strbuf_add_commented_lines(buf, explanation, strlen(explanation));
}