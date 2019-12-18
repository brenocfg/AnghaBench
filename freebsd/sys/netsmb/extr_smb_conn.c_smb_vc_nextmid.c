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
typedef  scalar_t__ u_short ;
struct TYPE_2__ {int /*<<< orphan*/  co_interlock; } ;
struct smb_vc {TYPE_1__ obj; int /*<<< orphan*/  vc_mid; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

u_short
smb_vc_nextmid(struct smb_vc *vcp)
{
	u_short r;
	
	sx_xlock(&vcp->obj.co_interlock);
	r = vcp->vc_mid++;
	sx_unlock(&vcp->obj.co_interlock);
	return r;
}