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
struct TYPE_2__ {char* yesstr; char* nostr; char* yesexpr; char* noexpr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  close_category (int /*<<< orphan*/ *) ; 
 TYPE_1__ msgs ; 
 int /*<<< orphan*/ * open_category () ; 
 scalar_t__ putl_category (char*,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
dump_messages(void)
{
	FILE *f;
	char *ptr;

	if (msgs.yesstr == NULL) {
		warn("missing field 'yesstr'");
		msgs.yesstr = "";
	}
	if (msgs.nostr == NULL) {
		warn("missing field 'nostr'");
		msgs.nostr = "";
	}

	/*
	 * CLDR likes to add : separated lists for yesstr and nostr.
	 * Legacy Solaris code does not seem to grok this.  Fix it.
	 */
	if ((ptr = strchr(msgs.yesstr, ':')) != NULL)
		*ptr = 0;
	if ((ptr = strchr(msgs.nostr, ':')) != NULL)
		*ptr = 0;

	if ((f = open_category()) == NULL) {
		return;
	}

	if ((putl_category(msgs.yesexpr, f) == EOF) ||
	    (putl_category(msgs.noexpr, f) == EOF) ||
	    (putl_category(msgs.yesstr, f) == EOF) ||
	    (putl_category(msgs.nostr, f) == EOF)) {
		return;
	}
	close_category(f);
}