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
struct t4_sge_context {long cid; int /*<<< orphan*/  mem_id; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_GET_SGE_CONTEXT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SGE_CONTEXT_CNM ; 
 int /*<<< orphan*/  SGE_CONTEXT_EGRESS ; 
 int /*<<< orphan*/  SGE_CONTEXT_FLM ; 
 int /*<<< orphan*/  SGE_CONTEXT_INGRESS ; 
 int chip_id ; 
 int doit (int /*<<< orphan*/ ,struct t4_sge_context*) ; 
 int /*<<< orphan*/  show_t4_ctxt (struct t4_sge_context*) ; 
 int /*<<< orphan*/  show_t5t6_ctxt (struct t4_sge_context*,int) ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
get_sge_context(int argc, const char *argv[])
{
	int rc;
	char *p;
	long cid;
	struct t4_sge_context cntxt = {0};

	if (argc != 2) {
		warnx("sge_context: incorrect number of arguments.");
		return (EINVAL);
	}

	if (!strcmp(argv[0], "egress"))
		cntxt.mem_id = SGE_CONTEXT_EGRESS;
	else if (!strcmp(argv[0], "ingress"))
		cntxt.mem_id = SGE_CONTEXT_INGRESS;
	else if (!strcmp(argv[0], "fl"))
		cntxt.mem_id = SGE_CONTEXT_FLM;
	else if (!strcmp(argv[0], "cong"))
		cntxt.mem_id = SGE_CONTEXT_CNM;
	else {
		warnx("unknown context type \"%s\"; known types are egress, "
		    "ingress, fl, and cong.", argv[0]);
		return (EINVAL);
	}

	p = str_to_number(argv[1], &cid, NULL);
	if (*p) {
		warnx("invalid context id \"%s\"", argv[1]);
		return (EINVAL);
	}
	cntxt.cid = cid;

	rc = doit(CHELSIO_T4_GET_SGE_CONTEXT, &cntxt);
	if (rc != 0)
		return (rc);

	if (chip_id == 4)
		show_t4_ctxt(&cntxt);
	else
		show_t5t6_ctxt(&cntxt, chip_id);

	return (0);
}