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
struct sctp_nxtinfo {int nxt_sid; int nxt_length; int nxt_assoc_id; int /*<<< orphan*/  nxt_ppid; int /*<<< orphan*/  nxt_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_mask_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdecode_sctp_nxt_flags ; 

__attribute__((used)) static void
print_sctp_nxtinfo(FILE *fp, struct sctp_nxtinfo *info)
{
	fprintf(fp, "{sid=%u,", info->nxt_sid);
	fputs("flgs=", fp);
	print_mask_arg(sysdecode_sctp_nxt_flags, fp, info->nxt_flags);
	fprintf(fp, ",ppid=%u,", ntohl(info->nxt_ppid));
	fprintf(fp, "len=%u,", info->nxt_length);
	fprintf(fp, "id=%u}", info->nxt_assoc_id);
}