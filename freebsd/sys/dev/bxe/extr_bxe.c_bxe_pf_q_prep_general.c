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
typedef  int /*<<< orphan*/  uint8_t ;
struct ecore_general_setup_params {int /*<<< orphan*/  cos; int /*<<< orphan*/  mtu; int /*<<< orphan*/  spcl_id; int /*<<< orphan*/  stat_id; } ;
struct bxe_softc {int /*<<< orphan*/  mtu; } ;
struct bxe_fastpath {int /*<<< orphan*/  cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_stats_id (struct bxe_fastpath*) ; 

__attribute__((used)) static void
bxe_pf_q_prep_general(struct bxe_softc                  *sc,
                      struct bxe_fastpath               *fp,
                      struct ecore_general_setup_params *gen_init,
                      uint8_t                           cos)
{
    gen_init->stat_id = bxe_stats_id(fp);
    gen_init->spcl_id = fp->cl_id;
    gen_init->mtu = sc->mtu;
    gen_init->cos = cos;
}