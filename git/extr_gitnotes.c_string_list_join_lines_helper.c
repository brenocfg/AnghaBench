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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int string_list_join_lines_helper(struct string_list_item *item,
					 void *cb_data)
{
	struct strbuf *buf = cb_data;
	strbuf_addstr(buf, item->string);
	strbuf_addch(buf, '\n');
	return 0;
}