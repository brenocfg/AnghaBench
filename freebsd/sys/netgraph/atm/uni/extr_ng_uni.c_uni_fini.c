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
struct unimem_debug {char* file; int lno; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 struct unimem_debug* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct unimem_debug*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_UNI ; 
 size_t UNIMEM_TYPES ; 
 int /*<<< orphan*/  free (struct unimem_debug*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nguni_freemem ; 
 int /*<<< orphan*/  nguni_unilist_mtx ; 
 int /*<<< orphan*/ * nguni_usedmem ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,char*,int) ; 
 char** unimem_names ; 

__attribute__((used)) static void
uni_fini(void)
{
	u_int type;
	struct unimem_debug *h;

	for (type = 0; type < UNIMEM_TYPES; type++) {
		while ((h = LIST_FIRST(&nguni_freemem[type])) != NULL) {
			LIST_REMOVE(h, link);
			free(h, M_UNI);
		}

		while ((h = LIST_FIRST(&nguni_usedmem[type])) != NULL) {
			LIST_REMOVE(h, link);
			printf("ng_uni: %s in use: %p (%s,%u)\n",
			    unimem_names[type], (caddr_t)h->data,
			    h->file, h->lno);
			free(h, M_UNI);
		}
	}

	mtx_destroy(&nguni_unilist_mtx);
}