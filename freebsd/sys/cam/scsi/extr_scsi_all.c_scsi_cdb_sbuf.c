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
typedef  int u_int8_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int) ; 

void
scsi_cdb_sbuf(u_int8_t *cdb_ptr, struct sbuf *sb)
{
	u_int8_t cdb_len;
	int i;

	if (cdb_ptr == NULL)
		return;

	/*
	 * This is taken from the SCSI-3 draft spec.
	 * (T10/1157D revision 0.3)
	 * The top 3 bits of an opcode are the group code.  The next 5 bits
	 * are the command code.
	 * Group 0:  six byte commands
	 * Group 1:  ten byte commands
	 * Group 2:  ten byte commands
	 * Group 3:  reserved
	 * Group 4:  sixteen byte commands
	 * Group 5:  twelve byte commands
	 * Group 6:  vendor specific
	 * Group 7:  vendor specific
	 */
	switch((*cdb_ptr >> 5) & 0x7) {
		case 0:
			cdb_len = 6;
			break;
		case 1:
		case 2:
			cdb_len = 10;
			break;
		case 3:
		case 6:
		case 7:
			/* in this case, just print out the opcode */
			cdb_len = 1;
			break;
		case 4:
			cdb_len = 16;
			break;
		case 5:
			cdb_len = 12;
			break;
	}

	for (i = 0; i < cdb_len; i++)
		sbuf_printf(sb, "%02hhx ", cdb_ptr[i]);

	return;
}