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
struct ddf_meta {int /*<<< orphan*/ * bbm; int /*<<< orphan*/ * pdd; int /*<<< orphan*/ * cr; int /*<<< orphan*/ * vdr; int /*<<< orphan*/ * pdr; int /*<<< orphan*/ * cdr; int /*<<< orphan*/ * hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_DDF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ddf_meta_free(struct ddf_meta *meta)
{

	if (meta->hdr != NULL) {
		free(meta->hdr, M_MD_DDF);
		meta->hdr = NULL;
	}
	if (meta->cdr != NULL) {
		free(meta->cdr, M_MD_DDF);
		meta->cdr = NULL;
	}
	if (meta->pdr != NULL) {
		free(meta->pdr, M_MD_DDF);
		meta->pdr = NULL;
	}
	if (meta->vdr != NULL) {
		free(meta->vdr, M_MD_DDF);
		meta->vdr = NULL;
	}
	if (meta->cr != NULL) {
		free(meta->cr, M_MD_DDF);
		meta->cr = NULL;
	}
	if (meta->pdd != NULL) {
		free(meta->pdd, M_MD_DDF);
		meta->pdd = NULL;
	}
	if (meta->bbm != NULL) {
		free(meta->bbm, M_MD_DDF);
		meta->bbm = NULL;
	}
}