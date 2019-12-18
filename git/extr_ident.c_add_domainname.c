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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_NAME_MAX ; 
 scalar_t__ canonical_name (char*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  warning_errno (char*) ; 
 scalar_t__ xgethostname (char*,int) ; 

__attribute__((used)) static void add_domainname(struct strbuf *out, int *is_bogus)
{
	char buf[HOST_NAME_MAX + 1];

	if (xgethostname(buf, sizeof(buf))) {
		warning_errno("cannot get host name");
		strbuf_addstr(out, "(none)");
		*is_bogus = 1;
		return;
	}
	if (strchr(buf, '.'))
		strbuf_addstr(out, buf);
	else if (canonical_name(buf, out) < 0) {
		strbuf_addf(out, "%s.(none)", buf);
		*is_bogus = 1;
	}
}