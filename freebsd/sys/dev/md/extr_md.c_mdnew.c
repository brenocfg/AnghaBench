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
struct md_s {int type; int unit; int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  stat_mtx; int /*<<< orphan*/  name; int /*<<< orphan*/  procp; int /*<<< orphan*/  bio_queue; } ;
typedef  enum md_types { ____Placeholder_md_types } md_types ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct md_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct md_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_MD ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int alloc_unr_specific (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct md_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int kproc_create (int /*<<< orphan*/ ,struct md_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  md_kthread ; 
 int /*<<< orphan*/  md_softc_list ; 
 int /*<<< orphan*/  md_uh ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct md_s *
mdnew(int unit, int *errp, enum md_types type)
{
	struct md_s *sc;
	int error;

	*errp = 0;
	if (unit == -1)
		unit = alloc_unr(md_uh);
	else
		unit = alloc_unr_specific(md_uh, unit);

	if (unit == -1) {
		*errp = EBUSY;
		return (NULL);
	}

	sc = (struct md_s *)malloc(sizeof *sc, M_MD, M_WAITOK | M_ZERO);
	sc->type = type;
	bioq_init(&sc->bio_queue);
	mtx_init(&sc->queue_mtx, "md bio queue", NULL, MTX_DEF);
	mtx_init(&sc->stat_mtx, "md stat", NULL, MTX_DEF);
	sc->unit = unit;
	sprintf(sc->name, "md%d", unit);
	LIST_INSERT_HEAD(&md_softc_list, sc, list);
	error = kproc_create(md_kthread, sc, &sc->procp, 0, 0,"%s", sc->name);
	if (error == 0)
		return (sc);
	LIST_REMOVE(sc, list);
	mtx_destroy(&sc->stat_mtx);
	mtx_destroy(&sc->queue_mtx);
	free_unr(md_uh, sc->unit);
	free(sc, M_MD);
	*errp = error;
	return (NULL);
}