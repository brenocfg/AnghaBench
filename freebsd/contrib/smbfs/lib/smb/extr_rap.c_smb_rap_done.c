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
struct smb_rap {struct smb_rap* r_sdata; struct smb_rap* r_sparam; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct smb_rap*) ; 

void
smb_rap_done(struct smb_rap *rap)
{
	if (rap->r_sparam)
		free(rap->r_sparam);
	if (rap->r_sdata)
		free(rap->r_sdata);
	free(rap);
}