#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ncha; int /*<<< orphan*/  rchash; int /*<<< orphan*/  rcrecs; } ;
typedef  TYPE_1__ xdlclassifier_t ;

/* Variables and functions */
 int /*<<< orphan*/  xdl_cha_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xdl_free_classifier(xdlclassifier_t *cf) {

	xdl_free(cf->rcrecs);
	xdl_free(cf->rchash);
	xdl_cha_free(&cf->ncha);
}