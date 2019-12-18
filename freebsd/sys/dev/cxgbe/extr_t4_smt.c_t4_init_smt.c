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
struct smt_entry {int idx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct smt_data {int smt_size; struct smt_entry* smtab; int /*<<< orphan*/  lock; } ;
struct adapter {struct smt_data* smt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_ZERO ; 
 int SMT_SIZE ; 
 int /*<<< orphan*/  SMT_STATE_UNUSED ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct smt_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

int
t4_init_smt(struct adapter *sc, int flags)
{
	int i, smt_size;
	struct smt_data *s;

	smt_size = SMT_SIZE;
	s = malloc(sizeof(*s) + smt_size * sizeof (struct smt_entry), M_CXGBE,
	    M_ZERO | flags);
	if (!s)
		return (ENOMEM);

	s->smt_size = smt_size;
	rw_init(&s->lock, "SMT");

	for (i = 0; i < smt_size; i++) {
		struct smt_entry *e = &s->smtab[i];

		e->idx = i;
		e->state = SMT_STATE_UNUSED;
		mtx_init(&e->lock, "SMT_E", NULL, MTX_DEF);
		atomic_store_rel_int(&e->refcnt, 0);
	}

	sc->smt = s;

	return (0);
}