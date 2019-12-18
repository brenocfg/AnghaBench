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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SCTP_PR_SCTP_ALL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int print_mask_0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sctpsinfoflags ; 
 char* sysdecode_sctp_pr_policy (int) ; 

void
sysdecode_sctp_sinfo_flags(FILE *fp, int sinfo_flags)
{
	const char *temp;
	int rem;
	bool printed;

	printed = print_mask_0(fp, sctpsinfoflags, sinfo_flags, &rem);
	if (rem & ~SCTP_PR_SCTP_ALL) {
		fprintf(fp, "%s%#x", printed ? "|" : "", rem & ~SCTP_PR_SCTP_ALL);
		printed = true;
		rem &= ~SCTP_PR_SCTP_ALL;
	}
	if (rem != 0) {
		temp = sysdecode_sctp_pr_policy(rem);
		if (temp != NULL) {
			fprintf(fp, "%s%s", printed ? "|" : "", temp);
		} else {
			fprintf(fp, "%s%#x", printed ? "|" : "", rem);
		}
	}
}