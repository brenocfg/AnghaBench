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
typedef  size_t u_int ;
struct atp_softc {int /*<<< orphan*/ * sc_strokes_data; int /*<<< orphan*/  sc_stroke_free; scalar_t__ sc_n_strokes; int /*<<< orphan*/  sc_stroke_used; } ;

/* Variables and functions */
 size_t ATP_MAX_STROKES ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
atp_init_stroke_pool(struct atp_softc *sc)
{
	u_int x;

	TAILQ_INIT(&sc->sc_stroke_free);
	TAILQ_INIT(&sc->sc_stroke_used);

	sc->sc_n_strokes = 0;

	memset(&sc->sc_strokes_data, 0, sizeof(sc->sc_strokes_data));

	for (x = 0; x != ATP_MAX_STROKES; x++) {
		TAILQ_INSERT_TAIL(&sc->sc_stroke_free, &sc->sc_strokes_data[x],
		    entry);
	}
}