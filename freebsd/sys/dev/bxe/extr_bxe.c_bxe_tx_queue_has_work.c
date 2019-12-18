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
typedef  scalar_t__ uint16_t ;
struct bxe_fastpath {scalar_t__ tx_pkt_cons; int /*<<< orphan*/ * tx_cons_sb; } ;

/* Variables and functions */
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline int
bxe_tx_queue_has_work(struct bxe_fastpath *fp)
{
    uint16_t hw_cons;

    mb(); /* status block fields can change */
    hw_cons = le16toh(*fp->tx_cons_sb);
    return (hw_cons != fp->tx_pkt_cons);
}