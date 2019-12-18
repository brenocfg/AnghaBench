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
struct uni_msg {int /*<<< orphan*/ * b_buf; int /*<<< orphan*/ * b_lim; int /*<<< orphan*/ * b_wptr; int /*<<< orphan*/ * b_rptr; } ;
struct ngatm_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ EXTRA ; 
 struct ngatm_msg* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ngatm_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ngatm_msg*,int /*<<< orphan*/ ) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_UNIMSG ; 
 int /*<<< orphan*/  M_UNIMSGHDR ; 
 int M_ZERO ; 
 int /*<<< orphan*/  link ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngatm_freeuni ; 
 int /*<<< orphan*/  ngatm_unilist_mtx ; 

struct uni_msg *
uni_msg_alloc(size_t s)
{
	struct ngatm_msg *a;
	struct uni_msg *m;

	mtx_lock(&ngatm_unilist_mtx);
	if ((a = LIST_FIRST(&ngatm_freeuni)) != NULL)
		LIST_REMOVE(a, link);
	mtx_unlock(&ngatm_unilist_mtx);

	if (a == NULL) {
		if ((m = malloc(sizeof(*m), M_UNIMSGHDR, M_NOWAIT)) == NULL)
			return (NULL);
		a = (struct ngatm_msg *)m;
	} else
		m = (struct uni_msg *)a;

	s += EXTRA;
	if((m->b_buf = malloc(s, M_UNIMSG, M_NOWAIT | M_ZERO)) == NULL) {
		mtx_lock(&ngatm_unilist_mtx);
		LIST_INSERT_HEAD(&ngatm_freeuni, a, link);
		mtx_unlock(&ngatm_unilist_mtx);
		return (NULL);
	}
	m->b_rptr = m->b_wptr = m->b_buf;
	m->b_lim = m->b_buf + s;

	return (m);
}