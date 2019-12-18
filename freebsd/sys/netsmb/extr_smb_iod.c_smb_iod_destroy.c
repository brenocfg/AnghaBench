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
struct smbiod {int dummy; } ;

/* Variables and functions */
 int SMBIOD_EV_SHUTDOWN ; 
 int SMBIOD_EV_SYNC ; 
 int /*<<< orphan*/  smb_iod_request (struct smbiod*,int,int /*<<< orphan*/ *) ; 

int
smb_iod_destroy(struct smbiod *iod)
{
	smb_iod_request(iod, SMBIOD_EV_SHUTDOWN | SMBIOD_EV_SYNC, NULL);
	return 0;
}