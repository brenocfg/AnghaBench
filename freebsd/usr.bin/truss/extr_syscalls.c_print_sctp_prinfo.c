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
struct sctp_prinfo {int pr_value; int /*<<< orphan*/  pr_policy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_integer_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdecode_sctp_pr_policy ; 

__attribute__((used)) static void
print_sctp_prinfo(FILE *fp, struct sctp_prinfo *info)
{
	fputs("{pol=", fp);
	print_integer_arg(sysdecode_sctp_pr_policy, fp, info->pr_policy);
	fprintf(fp, ",val=%u}", info->pr_value);
}