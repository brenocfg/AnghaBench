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
struct ccb_ataio {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_cmd_sbuf (int /*<<< orphan*/ *,struct sbuf*) ; 
 int /*<<< orphan*/  ata_op_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 

int
ata_command_sbuf(struct ccb_ataio *ataio, struct sbuf *sb)
{

	sbuf_printf(sb, "%s. ACB: ",
	    ata_op_string(&ataio->cmd));
	ata_cmd_sbuf(&ataio->cmd, sb);

	return(0);
}