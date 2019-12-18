#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pbt; } ;
struct TYPE_6__ {TYPE_1__ pb0_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_LINE_SIZE ; 
#define  IPL_PBT_CCW 129 
#define  IPL_PBT_FCP 128 
 char* early_command_line ; 
 TYPE_2__ ipl_block ; 
 size_t ipl_block_get_ascii_scpdata (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t ipl_block_get_ascii_vmparm (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void append_ipl_block_parm(void)
{
	char *parm, *delim;
	size_t len, rc = 0;

	len = strlen(early_command_line);

	delim = early_command_line + len;    /* '\0' character position */
	parm = early_command_line + len + 1; /* append right after '\0' */

	switch (ipl_block.pb0_hdr.pbt) {
	case IPL_PBT_CCW:
		rc = ipl_block_get_ascii_vmparm(
			parm, COMMAND_LINE_SIZE - len - 1, &ipl_block);
		break;
	case IPL_PBT_FCP:
		rc = ipl_block_get_ascii_scpdata(
			parm, COMMAND_LINE_SIZE - len - 1, &ipl_block);
		break;
	}
	if (rc) {
		if (*parm == '=')
			memmove(early_command_line, parm + 1, rc);
		else
			*delim = ' '; /* replace '\0' with space */
	}
}