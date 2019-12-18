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
typedef  char SesDiagPageCodes ;

/* Variables and functions */
 int CAM_DIR_IN ; 
 char RECEIVE_DIAGNOSTIC ; 
 char SEND_DIAGNOSTIC ; 

__attribute__((used)) static void
ses_page_cdb(char *cdb, int bufsiz, SesDiagPageCodes pagenum, int dir)
{

	/* Ref: SPC-4 r25 Section 6.20 Table 223 */
	if (dir == CAM_DIR_IN) {
		cdb[0] = RECEIVE_DIAGNOSTIC;
		cdb[1] = 1; /* Set page code valid bit */
		cdb[2] = pagenum;
	} else {
		cdb[0] = SEND_DIAGNOSTIC;
		cdb[1] = 0x10;
		cdb[2] = pagenum;
	}
	cdb[3] = bufsiz >> 8;	/* high bits */
	cdb[4] = bufsiz & 0xff;	/* low bits */
	cdb[5] = 0;
}