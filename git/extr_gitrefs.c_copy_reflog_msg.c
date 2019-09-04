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
 int isspace (char) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 

void copy_reflog_msg(struct strbuf *sb, const char *msg)
{
	char c;
	int wasspace = 1;

	strbuf_addch(sb, '\t');
	while ((c = *msg++)) {
		if (wasspace && isspace(c))
			continue;
		wasspace = isspace(c);
		if (wasspace)
			c = ' ';
		strbuf_addch(sb, c);
	}
	strbuf_rtrim(sb);
}