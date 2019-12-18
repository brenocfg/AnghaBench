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
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSTOCP (struct smb_share*) ; 
 int /*<<< orphan*/  smb_co_put (int /*<<< orphan*/ ,struct smb_cred*) ; 

void
smb_share_put(struct smb_share *ssp, struct smb_cred *scred)
{
	
	smb_co_put(SSTOCP(ssp), scred);
}