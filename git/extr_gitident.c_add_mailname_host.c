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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning_errno (char*) ; 

__attribute__((used)) static int add_mailname_host(struct strbuf *buf)
{
	FILE *mailname;
	struct strbuf mailnamebuf = STRBUF_INIT;

	mailname = fopen_or_warn("/etc/mailname", "r");
	if (!mailname)
		return -1;

	if (strbuf_getline(&mailnamebuf, mailname) == EOF) {
		if (ferror(mailname))
			warning_errno("cannot read /etc/mailname");
		strbuf_release(&mailnamebuf);
		fclose(mailname);
		return -1;
	}
	/* success! */
	strbuf_addbuf(buf, &mailnamebuf);
	strbuf_release(&mailnamebuf);
	fclose(mailname);
	return 0;
}