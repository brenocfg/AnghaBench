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
struct sbuf {int dummy; } ;
struct ccb_smpio {int /*<<< orphan*/  smp_request_len; int /*<<< orphan*/ * smp_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_command_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sbuf*,char*,int,int) ; 
 int /*<<< orphan*/  smp_command_desc (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void
smp_command_sbuf(struct ccb_smpio *smpio, struct sbuf *sb,
		 char *line_prefix, int first_line_len, int line_len)
{
	sbuf_printf(sb, "%s. ", smp_command_desc(smpio->smp_request[1]));

	/*
	 * Acccount for the command description and the period and space
	 * after the command description.
	 */
	first_line_len -= strlen(smp_command_desc(smpio->smp_request[1])) + 2;

	smp_command_decode(smpio->smp_request, smpio->smp_request_len, sb,
			   line_prefix, first_line_len, line_len);
}