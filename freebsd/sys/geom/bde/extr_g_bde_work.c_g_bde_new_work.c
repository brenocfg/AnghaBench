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
struct g_bde_work {struct g_bde_softc* softc; int /*<<< orphan*/  state; } ;
struct g_bde_softc {int /*<<< orphan*/  worklist; int /*<<< orphan*/  nwork; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GBDE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_bde_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bde_nwork ; 
 int /*<<< orphan*/  list ; 
 struct g_bde_work* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct g_bde_work *
g_bde_new_work(struct g_bde_softc *sc)
{
	struct g_bde_work *wp;

	wp = malloc(sizeof *wp, M_GBDE, M_NOWAIT | M_ZERO);
	if (wp == NULL)
		return (wp);
	wp->state = SETUP;
	wp->softc = sc;
	g_bde_nwork++;
	sc->nwork++;
	TAILQ_INSERT_TAIL(&sc->worklist, wp, list);
	return (wp);
}