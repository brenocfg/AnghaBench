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
struct credential_operation {int (* op ) (struct credential*) ;scalar_t__ name; } ;
struct credential {int dummy; } ;

/* Variables and functions */
 struct credential CREDENTIAL_INIT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  credential_clear (struct credential*) ; 
 struct credential_operation* credential_helper_ops ; 
 int credential_read (struct credential*) ; 
 int /*<<< orphan*/  credential_write (struct credential*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_set_application_name (char*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int stub1 (struct credential*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;

	struct credential_operation const *try_op = credential_helper_ops;
	struct credential cred = CREDENTIAL_INIT;

	if (!argv[1]) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	g_set_application_name("Git Credential Helper");

	/* lookup operation callback */
	while (try_op->name && strcmp(argv[1], try_op->name))
		try_op++;

	/* unsupported operation given -- ignore silently */
	if (!try_op->name || !try_op->op)
		goto out;

	ret = credential_read(&cred);
	if (ret)
		goto out;

	/* perform credential operation */
	ret = (*try_op->op)(&cred);

	credential_write(&cred);

out:
	credential_clear(&cred);
	return ret;
}