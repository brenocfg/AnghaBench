#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_active_node; int /*<<< orphan*/  mctx; TYPE_2__* head; } ;
typedef  TYPE_1__ isc_radix_tree_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** data; int /*<<< orphan*/ * prefix; struct TYPE_6__* r; struct TYPE_6__* l; } ;
typedef  TYPE_2__ isc_radix_node_t ;
typedef  int /*<<< orphan*/  (* isc_radix_destroyfunc_t ) (int /*<<< orphan*/ **) ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  RADIX_MAXBITS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  _deref_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void
_clear_radix(isc_radix_tree_t *radix, isc_radix_destroyfunc_t func) {

	REQUIRE(radix != NULL);

	if (radix->head != NULL) {

		isc_radix_node_t *Xstack[RADIX_MAXBITS+1];
		isc_radix_node_t **Xsp = Xstack;
		isc_radix_node_t *Xrn = radix->head;

		while (Xrn != NULL) {
			isc_radix_node_t *l = Xrn->l;
			isc_radix_node_t *r = Xrn->r;

			if (Xrn->prefix != NULL) {
				_deref_prefix(radix->mctx, Xrn->prefix);
				if (func != NULL && (Xrn->data[0] != NULL ||
						     Xrn->data[1] != NULL))
					func(Xrn->data);
			} else {
				INSIST(Xrn->data[0] == NULL &&
				       Xrn->data[1] == NULL);
			}

			isc_mem_put(radix->mctx, Xrn, sizeof(*Xrn));
			radix->num_active_node--;

			if (l != NULL) {
				if (r != NULL) {
					*Xsp++ = r;
				}
				Xrn = l;
			} else if (r != NULL) {
				Xrn = r;
			} else if (Xsp != Xstack) {
				Xrn = *(--Xsp);
			} else {
				Xrn = NULL;
			}
		}
	}
	RUNTIME_CHECK(radix->num_active_node == 0);
}