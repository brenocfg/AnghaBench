#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _citrus_iconv {TYPE_2__* cv_shared; } ;
struct TYPE_4__ {TYPE_1__* ci_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* io_uninit_context ) (struct _citrus_iconv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct _citrus_iconv*) ; 
 int /*<<< orphan*/  release_shared (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct _citrus_iconv*) ; 

void
_citrus_iconv_close(struct _citrus_iconv *cv)
{

	if (cv) {
		(*cv->cv_shared->ci_ops->io_uninit_context)(cv);
		release_shared(cv->cv_shared);
		free(cv);
	}
}