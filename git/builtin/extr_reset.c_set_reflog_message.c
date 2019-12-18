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
 char* getenv (char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void set_reflog_message(struct strbuf *sb, const char *action,
			       const char *rev)
{
	const char *rla = getenv("GIT_REFLOG_ACTION");

	strbuf_reset(sb);
	if (rla)
		strbuf_addf(sb, "%s: %s", rla, action);
	else if (rev)
		strbuf_addf(sb, "reset: moving to %s", rev);
	else
		strbuf_addf(sb, "reset: %s", action);
}