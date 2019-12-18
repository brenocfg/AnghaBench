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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bxe_softc {TYPE_1__ devinfo; } ;

/* Variables and functions */
 scalar_t__ INT_BLOCK_HC ; 
 int /*<<< orphan*/  bxe_hc_ack_int (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_igu_ack_int (struct bxe_softc*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline uint16_t
bxe_ack_int(struct bxe_softc *sc)
{
    mb();
    if (sc->devinfo.int_block == INT_BLOCK_HC) {
        return (bxe_hc_ack_int(sc));
    } else {
        return (bxe_igu_ack_int(sc));
    }
}