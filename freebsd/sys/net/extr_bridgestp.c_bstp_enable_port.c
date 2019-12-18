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
struct bstp_state {int dummy; } ;
struct bstp_port {int /*<<< orphan*/  bp_infois; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_INFO_AGED ; 

__attribute__((used)) static void
bstp_enable_port(struct bstp_state *bs, struct bstp_port *bp)
{
	bp->bp_infois = BSTP_INFO_AGED;
}