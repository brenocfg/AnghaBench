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
struct fdc_status {int* status; } ;

/* Variables and functions */
 int NE7_ST0_IC_AT ; 
 int NE7_ST0_IC_RC ; 
 int NE7_ST1_DE ; 
 int NE7_ST1_EN ; 
 int NE7_ST1_MA ; 
 int NE7_ST1_ND ; 
 int NE7_ST2_DD ; 
 int NE7_ST2_MD ; 
 int NE7_ST2_WC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
printstatus(struct fdc_status *fdcsp, int terse)
{
	char msgbuf[100];

	if (!terse)
		fprintf(stderr,
		"\nFDC status ST0=%#x ST1=%#x ST2=%#x C=%u H=%u R=%u N=%u:\n",
			fdcsp->status[0] & 0xff,
			fdcsp->status[1] & 0xff,
			fdcsp->status[2] & 0xff,
			fdcsp->status[3] & 0xff,
			fdcsp->status[4] & 0xff,
			fdcsp->status[5] & 0xff,
			fdcsp->status[6] & 0xff);

	if ((fdcsp->status[0] & NE7_ST0_IC_RC) == 0) {
		sprintf(msgbuf, "timeout");
	} else if ((fdcsp->status[0] & NE7_ST0_IC_RC) != NE7_ST0_IC_AT) {
		sprintf(msgbuf, "unexcpted interrupt code %#x",
			fdcsp->status[0] & NE7_ST0_IC_RC);
	} else {
		strcpy(msgbuf, "unexpected error code in ST1/ST2");

		if (fdcsp->status[1] & NE7_ST1_EN)
			strcpy(msgbuf, "end of cylinder (wrong format)");
		else if (fdcsp->status[1] & NE7_ST1_DE) {
			if (fdcsp->status[2] & NE7_ST2_DD)
				strcpy(msgbuf, "CRC error in data field");
			else
				strcpy(msgbuf, "CRC error in ID field");
		} else if (fdcsp->status[1] & NE7_ST1_MA) {
			if (fdcsp->status[2] & NE7_ST2_MD)
				strcpy(msgbuf, "no address mark in data field");
			else
				strcpy(msgbuf, "no address mark in ID field");
		} else if (fdcsp->status[2] & NE7_ST2_WC)
			strcpy(msgbuf, "wrong cylinder (format mismatch)");
		else if (fdcsp->status[1] & NE7_ST1_ND)
			strcpy(msgbuf, "no data (sector not found)");
	}
	fputs(msgbuf, stderr);
}