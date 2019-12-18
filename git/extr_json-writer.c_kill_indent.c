#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_2__ {int len; char* buf; } ;
struct json_writer {TYPE_1__ json; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void kill_indent(struct strbuf *sb,
			const struct json_writer *jw)
{
	int k;
	int eat_it = 0;

	strbuf_reset(sb);
	for (k = 0; k < jw->json.len; k++) {
		char ch = jw->json.buf[k];
		if (eat_it && ch == ' ')
			continue;
		if (ch == '\n') {
			eat_it = 1;
			continue;
		}
		eat_it = 0;
		strbuf_addch(sb, ch);
	}
}