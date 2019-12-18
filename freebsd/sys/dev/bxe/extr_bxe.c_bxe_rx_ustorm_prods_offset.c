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
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;
struct bxe_fastpath {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_qzone_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_USTRORM_INTMEM ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  SC_PORT (struct bxe_softc*) ; 
 scalar_t__ USTORM_RX_PRODS_E1X_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USTORM_RX_PRODS_E2_OFFSET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
bxe_rx_ustorm_prods_offset(struct bxe_softc    *sc,
                           struct bxe_fastpath *fp)
{
    uint32_t offset = BAR_USTRORM_INTMEM;

    if (!CHIP_IS_E1x(sc)) {
        offset += USTORM_RX_PRODS_E2_OFFSET(fp->cl_qzone_id);
    } else {
        offset += USTORM_RX_PRODS_E1X_OFFSET(SC_PORT(sc), fp->cl_id);
    }

    return (offset);
}