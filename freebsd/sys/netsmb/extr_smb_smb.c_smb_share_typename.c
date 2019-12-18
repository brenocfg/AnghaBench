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
#define  SMB_ST_ANY 132 
#define  SMB_ST_COMM 131 
#define  SMB_ST_DISK 130 
#define  SMB_ST_PIPE 129 
#define  SMB_ST_PRINTER 128 
 char* smb_any_share ; 

__attribute__((used)) static char *
smb_share_typename(int stype)
{
	char *pp;

	switch (stype) {
	    case SMB_ST_DISK:
		pp = "A:";
		break;
	    case SMB_ST_PRINTER:
		pp = smb_any_share;		/* can't use LPT: here... */
		break;
	    case SMB_ST_PIPE:
		pp = "IPC";
		break;
	    case SMB_ST_COMM:
		pp = "COMM";
		break;
	    case SMB_ST_ANY:
	    default:
		pp = smb_any_share;
		break;
	}
	return pp;
}