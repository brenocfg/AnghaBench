#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct timespec {int dummy; } ;
struct ddf_vol_meta {int sectorsize; TYPE_2__* vde; TYPE_2__* vdc; void* cdr; void* hdr; int /*<<< orphan*/  bigendian; } ;
struct ddf_vd_entry {int dummy; } ;
struct ddf_meta {int sectorsize; void* cdr; void* hdr; int /*<<< orphan*/  bigendian; } ;
struct clocktime {int year; int mon; int day; } ;
struct TYPE_6__ {int /*<<< orphan*/  Configuration_Record_Length; int /*<<< orphan*/  cd_length; } ;
struct TYPE_5__ {void* VD_GUID; } ;
struct TYPE_4__ {int /*<<< orphan*/  Sequence_Number; int /*<<< orphan*/  Signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDF_VDCR_SIGNATURE ; 
 int GET16 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET32 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MD_DDF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SET32 (struct ddf_vol_meta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int arc4random () ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 TYPE_3__* hdr ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  snprintf (void*,int,char*,int,int,int,int,int) ; 
 TYPE_1__* vdc ; 

__attribute__((used)) static void
ddf_vol_meta_create(struct ddf_vol_meta *meta, struct ddf_meta *sample)
{
	struct timespec ts;
	struct clocktime ct;
	u_int ss, size;

	meta->bigendian = sample->bigendian;
	ss = meta->sectorsize = sample->sectorsize;
	meta->hdr = malloc(ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->hdr, sample->hdr, ss);
	meta->cdr = malloc(GET32(sample, hdr->cd_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->cdr, sample->cdr, GET32(sample, hdr->cd_length) * ss);
	meta->vde = malloc(sizeof(struct ddf_vd_entry), M_MD_DDF, M_WAITOK);
	memset(meta->vde, 0xff, sizeof(struct ddf_vd_entry));
	getnanotime(&ts);
	clock_ts_to_ct(&ts, &ct);
	snprintf(meta->vde->VD_GUID, 25, "FreeBSD%04d%02d%02d%08x%01x",
	    ct.year, ct.mon, ct.day,
	    arc4random(), arc4random() & 0xf);
	size = GET16(sample, hdr->Configuration_Record_Length) * ss;
	meta->vdc = malloc(size, M_MD_DDF, M_WAITOK);
	memset(meta->vdc, 0xff, size);
	SET32(meta, vdc->Signature, DDF_VDCR_SIGNATURE);
	memcpy(meta->vdc->VD_GUID, meta->vde->VD_GUID, 24);
	SET32(meta, vdc->Sequence_Number, 0);
}