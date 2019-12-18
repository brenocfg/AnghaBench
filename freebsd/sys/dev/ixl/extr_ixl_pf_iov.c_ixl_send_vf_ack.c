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
typedef  int /*<<< orphan*/  uint16_t ;
struct ixl_vf {int dummy; } ;
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  ixl_send_vf_msg (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_send_vf_ack(struct ixl_pf *pf, struct ixl_vf *vf, uint16_t op)
{

	ixl_send_vf_msg(pf, vf, op, I40E_SUCCESS, NULL, 0);
}