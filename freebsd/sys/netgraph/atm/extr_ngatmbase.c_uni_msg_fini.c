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
struct ngatm_msg {int dummy; } ;

/* Variables and functions */
 struct ngatm_msg* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ngatm_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_UNIMSGHDR ; 
 int /*<<< orphan*/  free (struct ngatm_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngatm_freeuni ; 
 int /*<<< orphan*/  ngatm_unilist_mtx ; 

__attribute__((used)) static void
uni_msg_fini(void)
{
	struct ngatm_msg *h;

	/* free all free message headers */
	while ((h = LIST_FIRST(&ngatm_freeuni)) != NULL) {
		LIST_REMOVE(h, link);
		free(h, M_UNIMSGHDR);
	}

	mtx_destroy(&ngatm_unilist_mtx);
}