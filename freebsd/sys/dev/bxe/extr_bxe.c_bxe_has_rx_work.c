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
typedef  int uint16_t ;
struct bxe_fastpath {int rx_cq_cons; int /*<<< orphan*/ * rx_cq_cons_sb; } ;

/* Variables and functions */
 int RCQ_MAX ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline int
bxe_has_rx_work(struct bxe_fastpath *fp)
{
    uint16_t rx_cq_cons_sb;

    mb(); /* status block fields can change */
    rx_cq_cons_sb = le16toh(*fp->rx_cq_cons_sb);
    if ((rx_cq_cons_sb & RCQ_MAX) == RCQ_MAX)
        rx_cq_cons_sb++;
    return (fp->rx_cq_cons != rx_cq_cons_sb);
}