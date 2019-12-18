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
typedef  int /*<<< orphan*/  u16 ;
struct ioatdma_chan {int /*<<< orphan*/  issued; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_ring_size (struct ioatdma_chan*) ; 

__attribute__((used)) static inline u16 ioat_ring_pending(struct ioatdma_chan *ioat_chan)
{
	return CIRC_CNT(ioat_chan->head, ioat_chan->issued,
			ioat_ring_size(ioat_chan));
}