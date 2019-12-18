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
struct sctp_rcvinfo {int rcv_sid; int rcv_ssn; int rcv_tsn; int rcv_cumtsn; int rcv_context; int rcv_assoc_id; int /*<<< orphan*/  rcv_ppid; int /*<<< orphan*/  rcv_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_mask_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdecode_sctp_rcv_flags ; 

__attribute__((used)) static void
print_sctp_rcvinfo(FILE *fp, struct sctp_rcvinfo *info)
{
	fprintf(fp, "{sid=%u,", info->rcv_sid);
	fprintf(fp, "ssn=%u,", info->rcv_ssn);
	fputs("flgs=", fp);
	print_mask_arg(sysdecode_sctp_rcv_flags, fp, info->rcv_flags);
	fprintf(fp, ",ppid=%u,", ntohl(info->rcv_ppid));
	fprintf(fp, "tsn=%u,", info->rcv_tsn);
	fprintf(fp, "cumtsn=%u,", info->rcv_cumtsn);
	fprintf(fp, "ctx=%u,", info->rcv_context);
	fprintf(fp, "id=%u}", info->rcv_assoc_id);
}