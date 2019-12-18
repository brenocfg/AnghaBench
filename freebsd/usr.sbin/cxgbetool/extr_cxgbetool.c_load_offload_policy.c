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
struct t4_offload_policy {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_SET_OFLD_POLICY ; 
 int EINVAL ; 
 int doit (int /*<<< orphan*/ ,struct t4_offload_policy*) ; 
 int /*<<< orphan*/  free_offload_policy (struct t4_offload_policy*) ; 
 int parse_offload_policy (char const*,struct t4_offload_policy*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
load_offload_policy(int argc, const char *argv[])
{
	int rc = 0;
	const char *fname = argv[0];
	struct t4_offload_policy op = {0};

	if (argc != 1) {
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	if (!strcmp(fname, "clear") || !strcmp(fname, "none")) {
		/* op.nrules is 0 and that means clear policy */
		return (doit(CHELSIO_T4_SET_OFLD_POLICY, &op));
	}

	rc = parse_offload_policy(fname, &op);
	if (rc != 0) {
		/* Error message displayed already */
		return (EINVAL);
	}

	rc = doit(CHELSIO_T4_SET_OFLD_POLICY, &op);
	free_offload_policy(&op);

	return (rc);
}