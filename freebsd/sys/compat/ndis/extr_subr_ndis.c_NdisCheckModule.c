#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ndis_checkmodule {TYPE_1__* fh; int /*<<< orphan*/  afilename; } ;
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int caddr_t ;
struct TYPE_2__ {int nf_maplen; int /*<<< orphan*/  nf_type; int /*<<< orphan*/ * nf_map; int /*<<< orphan*/  nf_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_FH_TYPE_MODULE ; 
 scalar_t__ ndis_find_sym (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
NdisCheckModule(linker_file_t lf, void *context)
{
	struct ndis_checkmodule *nc;
	caddr_t			kldstart, kldend;

	nc = (struct ndis_checkmodule *)context;
	if (ndis_find_sym(lf, nc->afilename, "_start", &kldstart))
		return (0);
	if (ndis_find_sym(lf, nc->afilename, "_end", &kldend))
		return (0);
	nc->fh->nf_vp = lf;
	nc->fh->nf_map = NULL;
	nc->fh->nf_type = NDIS_FH_TYPE_MODULE;
	nc->fh->nf_maplen = (kldend - kldstart) & 0xFFFFFFFF;
	return (1);
}