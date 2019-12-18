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
struct sctp_sndinfo {int snd_sid; int snd_context; int snd_assoc_id; int /*<<< orphan*/  snd_ppid; int /*<<< orphan*/  snd_flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_mask_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdecode_sctp_snd_flags ; 

__attribute__((used)) static void
print_sctp_sndinfo(FILE *fp, struct sctp_sndinfo *info)
{
	fprintf(fp, "{sid=%u,", info->snd_sid);
	fputs("flgs=", fp);
	print_mask_arg(sysdecode_sctp_snd_flags, fp, info->snd_flags);
	fprintf(fp, ",ppid=%u,", ntohl(info->snd_ppid));
	fprintf(fp, "ctx=%u,", info->snd_context);
	fprintf(fp, "id=%u}", info->snd_assoc_id);
}