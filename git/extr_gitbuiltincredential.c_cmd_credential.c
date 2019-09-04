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
struct credential {int dummy; } ;

/* Variables and functions */
 struct credential CREDENTIAL_INIT ; 
 int /*<<< orphan*/  credential_approve (struct credential*) ; 
 int /*<<< orphan*/  credential_fill (struct credential*) ; 
 scalar_t__ credential_read (struct credential*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  credential_reject (struct credential*) ; 
 int /*<<< orphan*/  credential_write (struct credential*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_msg ; 

int cmd_credential(int argc, const char **argv, const char *prefix)
{
	const char *op;
	struct credential c = CREDENTIAL_INIT;

	if (argc != 2 || !strcmp(argv[1], "-h"))
		usage(usage_msg);
	op = argv[1];

	if (credential_read(&c, stdin) < 0)
		die("unable to read credential from stdin");

	if (!strcmp(op, "fill")) {
		credential_fill(&c);
		credential_write(&c, stdout);
	} else if (!strcmp(op, "approve")) {
		credential_approve(&c);
	} else if (!strcmp(op, "reject")) {
		credential_reject(&c);
	} else {
		usage(usage_msg);
	}
	return 0;
}