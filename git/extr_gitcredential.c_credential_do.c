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
struct credential {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int run_credential_helper (struct credential*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int credential_do(struct credential *c, const char *helper,
			 const char *operation)
{
	struct strbuf cmd = STRBUF_INIT;
	int r;

	if (helper[0] == '!')
		strbuf_addstr(&cmd, helper + 1);
	else if (is_absolute_path(helper))
		strbuf_addstr(&cmd, helper);
	else
		strbuf_addf(&cmd, "git credential-%s", helper);

	strbuf_addf(&cmd, " %s", operation);
	r = run_credential_helper(c, cmd.buf, !strcmp(operation, "get"));

	strbuf_release(&cmd);
	return r;
}