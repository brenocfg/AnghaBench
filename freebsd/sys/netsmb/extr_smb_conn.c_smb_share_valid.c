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
struct smb_share {scalar_t__ ss_tid; scalar_t__ ss_vcgenid; } ;
struct TYPE_2__ {scalar_t__ vc_genid; } ;

/* Variables and functions */
 scalar_t__ SMB_TID_UNKNOWN ; 
 TYPE_1__* SSTOVC (struct smb_share*) ; 

int
smb_share_valid(struct smb_share *ssp)
{
	return ssp->ss_tid != SMB_TID_UNKNOWN &&
	    ssp->ss_vcgenid == SSTOVC(ssp)->vc_genid;
}