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
struct _citrus_stdenc {scalar_t__ ce_module; struct _citrus_stdenc* ce_traits; struct _citrus_stdenc* ce_ops; int /*<<< orphan*/  (* eo_uninit ) (struct _citrus_stdenc*) ;scalar_t__ ce_closure; } ;

/* Variables and functions */
 struct _citrus_stdenc _citrus_stdenc_default ; 
 int /*<<< orphan*/  _citrus_unload_module (scalar_t__) ; 
 int /*<<< orphan*/  free (struct _citrus_stdenc*) ; 
 int /*<<< orphan*/  stub1 (struct _citrus_stdenc*) ; 

void
_citrus_stdenc_close(struct _citrus_stdenc *ce)
{

	if (ce == &_citrus_stdenc_default)
		return;

	if (ce->ce_module) {
		if (ce->ce_ops) {
			if (ce->ce_closure && ce->ce_ops->eo_uninit)
				(*ce->ce_ops->eo_uninit)(ce);
			free(ce->ce_ops);
		}
		free(ce->ce_traits);
		_citrus_unload_module(ce->ce_module);
	}
	free(ce);
}