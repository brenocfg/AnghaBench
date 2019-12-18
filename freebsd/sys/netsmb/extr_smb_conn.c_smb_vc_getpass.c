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
struct smb_vc {char const* vc_pass; } ;

/* Variables and functions */
 char const* smb_emptypass ; 

const char *
smb_vc_getpass(struct smb_vc *vcp)
{
	if (vcp->vc_pass)
		return vcp->vc_pass;
	return smb_emptypass;
}