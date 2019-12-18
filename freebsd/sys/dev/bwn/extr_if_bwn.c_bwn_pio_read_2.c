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
struct bwn_pio_txqueue {scalar_t__ tq_base; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 scalar_t__ BWN_READ_2 (struct bwn_mac*,scalar_t__) ; 

__attribute__((used)) static uint16_t
bwn_pio_read_2(struct bwn_mac *mac, struct bwn_pio_txqueue *tq,
    uint16_t offset)
{

	return (BWN_READ_2(mac, tq->tq_base + offset));
}