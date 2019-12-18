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
typedef  int u_int ;
struct ddf_meta {int sectorsize; int /*<<< orphan*/ * bbm; int /*<<< orphan*/ * pdd; int /*<<< orphan*/ * cr; int /*<<< orphan*/ * vdr; int /*<<< orphan*/ * pdr; int /*<<< orphan*/ * cdr; int /*<<< orphan*/ * hdr; int /*<<< orphan*/  bigendian; } ;
struct TYPE_2__ {int /*<<< orphan*/  bbmlog_length; int /*<<< orphan*/  pdd_length; int /*<<< orphan*/  cr_length; int /*<<< orphan*/  vdr_length; int /*<<< orphan*/  pdr_length; int /*<<< orphan*/  cd_length; } ;

/* Variables and functions */
 int GET32 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MD_DDF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 TYPE_1__* hdr ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ddf_meta_copy(struct ddf_meta *dst, struct ddf_meta *src)
{
	u_int ss;

	dst->bigendian = src->bigendian;
	ss = dst->sectorsize = src->sectorsize;
	dst->hdr = malloc(ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->hdr, src->hdr, ss);
	dst->cdr = malloc(GET32(src, hdr->cd_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->cdr, src->cdr, GET32(src, hdr->cd_length) * ss);
	dst->pdr = malloc(GET32(src, hdr->pdr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->pdr, src->pdr, GET32(src, hdr->pdr_length) * ss);
	dst->vdr = malloc(GET32(src, hdr->vdr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->vdr, src->vdr, GET32(src, hdr->vdr_length) * ss);
	dst->cr = malloc(GET32(src, hdr->cr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->cr, src->cr, GET32(src, hdr->cr_length) * ss);
	dst->pdd = malloc(GET32(src, hdr->pdd_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(dst->pdd, src->pdd, GET32(src, hdr->pdd_length) * ss);
	if (src->bbm != NULL) {
		dst->bbm = malloc(GET32(src, hdr->bbmlog_length) * ss, M_MD_DDF, M_WAITOK);
		memcpy(dst->bbm, src->bbm, GET32(src, hdr->bbmlog_length) * ss);
	}
}