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
typedef  int u_char ;
typedef  int /*<<< orphan*/  isc_session_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  sdebug (int,char*,int) ; 
 int /*<<< orphan*/  xdebug (char*,int) ; 

__attribute__((used)) static int
dwl(isc_session_t *sp, int lun, u_char *lp)
{
     debug_called(8);
     sdebug(4, "lun=%d", lun);
     /*
      | mapping LUN to iSCSI LUN
      | check the SAM-2 specs
      | hint: maxLUNS is a small number, cam's LUN is 32bits
      | iSCSI is 64bits, scsi is ?
      */
     // XXX: check if this will pass the endian test
     if(lun < 256) {
	  lp[0] = 0;
	  lp[1] = lun;
     } else
     if(lun < 16384) {
	  lp[0] = (1 << 5) | ((lun >> 8) & 0x3f);
	  lp[1] = lun & 0xff;
     } 
     else {
	  xdebug("lun %d: is unsupported!", lun);
	  return -1;
     }

     return 0;
}