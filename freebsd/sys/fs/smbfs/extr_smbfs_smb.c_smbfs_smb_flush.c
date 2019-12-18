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
struct smbnode {int n_flag; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int NFLUSHWIRE ; 
 int smb_smb_flush (struct smbnode*,struct smb_cred*) ; 

int
smbfs_smb_flush(struct smbnode *np, struct smb_cred *scred)
{
	if (np->n_flag & NFLUSHWIRE)
		return (smb_smb_flush(np, scred));
	return (0);
}