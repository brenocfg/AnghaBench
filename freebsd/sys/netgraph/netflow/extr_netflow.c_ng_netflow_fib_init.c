#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct fib_export {int dummy; } ;
typedef  TYPE_1__* priv_p ;
typedef  TYPE_2__* fib_export_p ;
struct TYPE_11__ {int fib; int domain_id; int /*<<< orphan*/  export9_mtx; int /*<<< orphan*/  export_mtx; } ;
struct TYPE_10__ {int /*<<< orphan*/  nfinfo_alloc_fibs; int /*<<< orphan*/ * fib_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int,TYPE_2__*,TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KTR_NET ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ atomic_cmpset_ptr (uintptr_t volatile*,uintptr_t,uintptr_t) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* priv_to_fib (TYPE_1__*,int) ; 

int
ng_netflow_fib_init(priv_p priv, int fib)
{
	fib_export_p	fe = priv_to_fib(priv, fib);

	CTR1(KTR_NET, "ng_netflow(): fib init: %d", fib);

	if (fe != NULL)
		return (0);

	if ((fe = malloc(sizeof(struct fib_export), M_NETGRAPH,
	    M_NOWAIT | M_ZERO)) == NULL)
		return (ENOMEM);

	mtx_init(&fe->export_mtx, "export dgram lock", NULL, MTX_DEF);
	mtx_init(&fe->export9_mtx, "export9 dgram lock", NULL, MTX_DEF);
	fe->fib = fib;
	fe->domain_id = fib;

	if (atomic_cmpset_ptr((volatile uintptr_t *)&priv->fib_data[fib],
	    (uintptr_t)NULL, (uintptr_t)fe) == 0) {
		/* FIB already set up by other ISR */
		CTR3(KTR_NET, "ng_netflow(): fib init: %d setup %p but got %p",
		    fib, fe, priv_to_fib(priv, fib));
		mtx_destroy(&fe->export_mtx);
		mtx_destroy(&fe->export9_mtx);
		free(fe, M_NETGRAPH);
	} else {
		/* Increase counter for statistics */
		CTR3(KTR_NET, "ng_netflow(): fib %d setup to %p (%p)",
		    fib, fe, priv_to_fib(priv, fib));
		priv->nfinfo_alloc_fibs++;
	}
	
	return (0);
}