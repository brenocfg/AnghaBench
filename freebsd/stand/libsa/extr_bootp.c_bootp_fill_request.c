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

/* Variables and functions */
 unsigned char TAG_CLASSID ; 
 unsigned char TAG_END ; 
 unsigned char TAG_GATEWAY ; 
 unsigned char TAG_HOSTNAME ; 
 unsigned char TAG_INTF_MTU ; 
 unsigned char TAG_PARAM_REQ ; 
 unsigned char TAG_ROOTPATH ; 
 unsigned char TAG_SERVERID ; 
 unsigned char TAG_SUBNET_MASK ; 
 unsigned char TAG_SWAPSERVER ; 
 unsigned char TAG_USER_CLASS ; 
 int /*<<< orphan*/  bcopy (char*,unsigned char*,int) ; 

__attribute__((used)) static void
bootp_fill_request(unsigned char *bp_vend)
{
	/*
	 * We are booting from PXE, we want to send the string
	 * 'PXEClient' to the DHCP server so you have the option of
	 * only responding to PXE aware dhcp requests.
	 */
	bp_vend[0] = TAG_CLASSID;
	bp_vend[1] = 9;
	bcopy("PXEClient", &bp_vend[2], 9);
	bp_vend[11] = TAG_USER_CLASS;
	/* len of each user class + number of user class */
	bp_vend[12] = 8;
	/* len of the first user class */
	bp_vend[13] = 7;
	bcopy("FreeBSD", &bp_vend[14], 7);
	bp_vend[21] = TAG_PARAM_REQ;
	bp_vend[22] = 7;
	bp_vend[23] = TAG_ROOTPATH;
	bp_vend[24] = TAG_HOSTNAME;
	bp_vend[25] = TAG_SWAPSERVER;
	bp_vend[26] = TAG_GATEWAY;
	bp_vend[27] = TAG_SUBNET_MASK;
	bp_vend[28] = TAG_INTF_MTU;
	bp_vend[29] = TAG_SERVERID;
	bp_vend[30] = TAG_END;
}