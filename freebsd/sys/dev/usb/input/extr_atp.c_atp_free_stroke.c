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
struct atp_softc {int /*<<< orphan*/  sc_stroke_free; int /*<<< orphan*/  sc_stroke_used; int /*<<< orphan*/  sc_n_strokes; } ;
typedef  int /*<<< orphan*/  atp_stroke_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 

__attribute__((used)) static void
atp_free_stroke(struct atp_softc *sc, atp_stroke_t *pstroke)
{
	if (pstroke == NULL)
		return;

	sc->sc_n_strokes--;

	TAILQ_REMOVE(&sc->sc_stroke_used, pstroke, entry);
	TAILQ_INSERT_TAIL(&sc->sc_stroke_free, pstroke, entry);
}