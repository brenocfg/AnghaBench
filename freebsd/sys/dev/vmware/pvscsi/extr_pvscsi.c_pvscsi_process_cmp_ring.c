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
typedef  int uint32_t ;
struct pvscsi_softc {struct pvscsi_ring_cmp_desc* cmp_ring; struct pvscsi_rings_state* rings_state; int /*<<< orphan*/  lock; } ;
struct pvscsi_rings_state {int cmp_cons_idx; int cmp_prod_idx; int /*<<< orphan*/  cmp_num_entries_log2; } ;
struct pvscsi_ring_cmp_desc {int dummy; } ;

/* Variables and functions */
 int MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_process_completion (struct pvscsi_softc*,struct pvscsi_ring_cmp_desc*) ; 

__attribute__((used)) static void
pvscsi_process_cmp_ring(struct pvscsi_softc *sc)
{
	struct pvscsi_ring_cmp_desc *ring;
	struct pvscsi_rings_state *s;
	struct pvscsi_ring_cmp_desc *e;
	uint32_t mask;

	mtx_assert(&sc->lock, MA_OWNED);

	s = sc->rings_state;
	ring = sc->cmp_ring;
	mask = MASK(s->cmp_num_entries_log2);

	while (s->cmp_cons_idx != s->cmp_prod_idx) {
		e = ring + (s->cmp_cons_idx & mask);

		pvscsi_process_completion(sc, e);

		mb();
		s->cmp_cons_idx++;
	}
}