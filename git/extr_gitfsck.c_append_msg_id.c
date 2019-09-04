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
 int /*<<< orphan*/  assert (char const) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  tolower (char) ; 

__attribute__((used)) static void append_msg_id(struct strbuf *sb, const char *msg_id)
{
	for (;;) {
		char c = *(msg_id)++;

		if (!c)
			break;
		if (c != '_')
			strbuf_addch(sb, tolower(c));
		else {
			assert(*msg_id);
			strbuf_addch(sb, *(msg_id)++);
		}
	}

	strbuf_addstr(sb, ": ");
}