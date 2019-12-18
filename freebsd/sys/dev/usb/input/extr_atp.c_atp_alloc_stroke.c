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
struct atp_softc {int /*<<< orphan*/  sc_n_strokes; int /*<<< orphan*/  sc_stroke_used; int /*<<< orphan*/  sc_stroke_free; } ;
typedef  int /*<<< orphan*/  atp_stroke_t ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static atp_stroke_t *
atp_alloc_stroke(struct atp_softc *sc)
{
	atp_stroke_t *pstroke;

	pstroke = TAILQ_FIRST(&sc->sc_stroke_free);
	if (pstroke == NULL)
		goto done;

	TAILQ_REMOVE(&sc->sc_stroke_free, pstroke, entry);
	memset(pstroke, 0, sizeof(*pstroke));
	TAILQ_INSERT_TAIL(&sc->sc_stroke_used, pstroke, entry);

	sc->sc_n_strokes++;
done:
	return (pstroke);
}