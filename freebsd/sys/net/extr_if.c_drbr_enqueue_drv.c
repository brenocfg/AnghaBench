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
struct mbuf {int dummy; } ;
struct buf_ring {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int drbr_enqueue (int /*<<< orphan*/ ,struct buf_ring*,struct mbuf*) ; 

int
drbr_enqueue_drv(if_t ifh, struct buf_ring *br, struct mbuf *m)
{
	return drbr_enqueue(ifh, br, m);

}