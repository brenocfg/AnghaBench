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
struct uni_msg {int /*<<< orphan*/  b_buf; } ;
struct ngatm_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ngatm_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_UNIMSG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngatm_freeuni ; 
 int /*<<< orphan*/  ngatm_unilist_mtx ; 

void
uni_msg_destroy(struct uni_msg *m)
{
	struct ngatm_msg *a;

	a = (struct ngatm_msg *)m;

	free(m->b_buf, M_UNIMSG);

	mtx_lock(&ngatm_unilist_mtx);
	LIST_INSERT_HEAD(&ngatm_freeuni, a, link);
	mtx_unlock(&ngatm_unilist_mtx);
}