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
typedef  scalar_t__ uint8_t ;
struct bxe_softc {int dummy; } ;
struct bxe_fastpath {scalar_t__ cl_id; struct bxe_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int FP_SB_MAX_E1x ; 
 int SC_PORT (struct bxe_softc*) ; 

__attribute__((used)) static inline uint8_t
bxe_stats_id(struct bxe_fastpath *fp)
{
    struct bxe_softc *sc = fp->sc;

    if (!CHIP_IS_E1x(sc)) {
        return (fp->cl_id);
    }

    return (fp->cl_id + SC_PORT(sc) * FP_SB_MAX_E1x);
}