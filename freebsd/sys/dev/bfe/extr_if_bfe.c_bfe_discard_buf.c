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
struct bfe_softc {struct bfe_desc* bfe_rx_list; struct bfe_rx_data* bfe_rx_ring; } ;
struct bfe_rx_data {int /*<<< orphan*/  bfe_ctrl; } ;
struct bfe_desc {int /*<<< orphan*/  bfe_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfe_discard_buf(struct bfe_softc *sc, int c)
{
	struct bfe_rx_data *r;
	struct bfe_desc *d;

	r = &sc->bfe_rx_ring[c];
	d = &sc->bfe_rx_list[c];
	d->bfe_ctrl = htole32(r->bfe_ctrl);
}