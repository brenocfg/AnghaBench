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
struct strbuf {char* buf; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  hash_object (char*,char const*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 scalar_t__ unquote_c_style (struct strbuf*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hash_stdin_paths(const char *type, int no_filters, unsigned flags,
			     int literally)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf unquoted = STRBUF_INIT;

	while (strbuf_getline(&buf, stdin) != EOF) {
		if (buf.buf[0] == '"') {
			strbuf_reset(&unquoted);
			if (unquote_c_style(&unquoted, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &unquoted);
		}
		hash_object(buf.buf, type, no_filters ? NULL : buf.buf, flags,
			    literally);
	}
	strbuf_release(&buf);
	strbuf_release(&unquoted);
}