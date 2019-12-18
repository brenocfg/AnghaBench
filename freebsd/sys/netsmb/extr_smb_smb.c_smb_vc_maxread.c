#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_2__ {int sv_caps; int sv_maxtx; } ;
struct smb_vc {int vc_hflags2; TYPE_1__ vc_sopt; } ;

/* Variables and functions */
 int SMB_CAP_LARGE_READX ; 
 int SMB_FLAGS2_SECURITY_SIGNATURE ; 
 int SMB_HDRLEN ; 

__attribute__((used)) static u_int32_t
smb_vc_maxread(struct smb_vc *vcp)
{
	/*
	 * Specs say up to 64k data bytes, but Windows traffic
	 * uses 60k... no doubt for some good reason.
	 *
	 * Don't exceed the server's buffer size if signatures
	 * are enabled otherwise Windows 2003 chokes. Allow space
	 * for the SMB header & a little bit extra.
	 */
	if ((vcp->vc_sopt.sv_caps & SMB_CAP_LARGE_READX) &&
	    (vcp->vc_hflags2 & SMB_FLAGS2_SECURITY_SIGNATURE) == 0)
		return (60*1024);
	else
		return (vcp->vc_sopt.sv_maxtx - SMB_HDRLEN - 64);
}