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
struct plug {int /*<<< orphan*/  ctx; struct common_plugin_method* dataptr; } ;
struct common_plugin_method {int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plug_free(void *ptr)
{
    struct plug *pl = ptr;
    if (pl->dataptr) {
	struct common_plugin_method *cpm = pl->dataptr;
	cpm->fini(pl->ctx);
    }
}