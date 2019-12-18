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
struct smbiod {int /*<<< orphan*/  iod_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBIOD_ST_DEAD ; 
 int /*<<< orphan*/  smb_iod_closetran (struct smbiod*) ; 
 int /*<<< orphan*/  smb_iod_invrq (struct smbiod*) ; 

__attribute__((used)) static void
smb_iod_dead(struct smbiod *iod)
{
	iod->iod_state = SMBIOD_ST_DEAD;
	smb_iod_closetran(iod);
	smb_iod_invrq(iod);
}