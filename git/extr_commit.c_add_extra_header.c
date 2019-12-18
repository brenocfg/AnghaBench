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
struct commit_extra_header {scalar_t__ len; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_add_lines (struct strbuf*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_extra_header(struct strbuf *buffer,
			     struct commit_extra_header *extra)
{
	strbuf_addstr(buffer, extra->key);
	if (extra->len)
		strbuf_add_lines(buffer, " ", extra->value, extra->len);
	else
		strbuf_addch(buffer, '\n');
}