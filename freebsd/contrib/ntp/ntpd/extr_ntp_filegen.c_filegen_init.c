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
struct TYPE_3__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  type; scalar_t__ id_hi; scalar_t__ id_lo; void* fname; void* dir; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__ FILEGEN ;

/* Variables and functions */
 int /*<<< orphan*/  FGEN_FLAG_LINK ; 
 int /*<<< orphan*/  FILEGEN_DAY ; 
 void* estrdup (char const*) ; 

__attribute__((used)) static void
filegen_init(
	const char *	dir,
	const char *	fname,
	FILEGEN *	fgp
	)
{
	fgp->fp = NULL;
	fgp->dir = estrdup(dir);
	fgp->fname = estrdup(fname);
	fgp->id_lo = 0;
	fgp->id_hi = 0;
	fgp->type = FILEGEN_DAY;
	fgp->flag = FGEN_FLAG_LINK; /* not yet enabled !!*/
}