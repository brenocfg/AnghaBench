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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void set_reflog_message(int argc, const char **argv)
{
	int i;
	struct strbuf msg = STRBUF_INIT;

	for (i = 0; i < argc; i++) {
		if (i)
			strbuf_addch(&msg, ' ');
		strbuf_addstr(&msg, argv[i]);
	}

	setenv("GIT_REFLOG_ACTION", msg.buf, 0);

	strbuf_release(&msg);
}