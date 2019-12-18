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
struct ddf_vol_meta {int /*<<< orphan*/ ** bvdc; int /*<<< orphan*/ * vdc; int /*<<< orphan*/ * vde; int /*<<< orphan*/ * cdr; int /*<<< orphan*/ * hdr; } ;

/* Variables and functions */
 int DDF_MAX_DISKS_HARD ; 
 int /*<<< orphan*/  M_MD_DDF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ddf_vol_meta_free(struct ddf_vol_meta *meta)
{
	int i;

	if (meta->hdr != NULL) {
		free(meta->hdr, M_MD_DDF);
		meta->hdr = NULL;
	}
	if (meta->cdr != NULL) {
		free(meta->cdr, M_MD_DDF);
		meta->cdr = NULL;
	}
	if (meta->vde != NULL) {
		free(meta->vde, M_MD_DDF);
		meta->vde = NULL;
	}
	if (meta->vdc != NULL) {
		free(meta->vdc, M_MD_DDF);
		meta->vdc = NULL;
	}
	for (i = 0; i < DDF_MAX_DISKS_HARD; i++) {
		if (meta->bvdc[i] != NULL) {
			free(meta->bvdc[i], M_MD_DDF);
			meta->bvdc[i] = NULL;
		}
	}
}