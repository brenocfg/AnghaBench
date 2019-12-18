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
struct bootp_packet {int* vend; } ;

/* Variables and functions */

__attribute__((used)) static int
bootpc_hascookie(struct bootp_packet *bp)
{

	return (bp->vend[0] == 99 && bp->vend[1] == 130 &&
		bp->vend[2] == 83 && bp->vend[3] == 99);
}