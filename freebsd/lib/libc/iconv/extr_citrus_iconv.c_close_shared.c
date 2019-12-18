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
struct _citrus_iconv_shared {scalar_t__ ci_module; struct _citrus_iconv_shared* ci_ops; int /*<<< orphan*/  (* io_uninit_shared ) (struct _citrus_iconv_shared*) ;scalar_t__ ci_closure; } ;

/* Variables and functions */
 int /*<<< orphan*/  _citrus_unload_module (scalar_t__) ; 
 int /*<<< orphan*/  free (struct _citrus_iconv_shared*) ; 
 int /*<<< orphan*/  stub1 (struct _citrus_iconv_shared*) ; 

__attribute__((used)) static __inline void
close_shared(struct _citrus_iconv_shared *ci)
{

	if (ci) {
		if (ci->ci_module) {
			if (ci->ci_ops) {
				if (ci->ci_closure)
					(*ci->ci_ops->io_uninit_shared)(ci);
				free(ci->ci_ops);
			}
			_citrus_unload_module(ci->ci_module);
		}
		free(ci);
	}
}