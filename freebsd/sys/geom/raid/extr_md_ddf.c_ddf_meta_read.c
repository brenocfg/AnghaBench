#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct g_provider {int sectorsize; int mediasize; int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_provider* provider; } ;
struct ddf_meta {int sectorsize; int bigendian; struct ddf_header* bbm; struct ddf_header* pdd; struct ddf_header* cr; struct ddf_header* vdr; struct ddf_header* pdr; struct ddf_header* cdr; struct ddf_header* hdr; } ;
struct ddf_header {scalar_t__ Signature; scalar_t__ Header_Type; int /*<<< orphan*/  bbmlog_length; int /*<<< orphan*/  bbmlog_section; int /*<<< orphan*/  pdd_length; int /*<<< orphan*/  pdd_section; int /*<<< orphan*/  cr_length; int /*<<< orphan*/  cr_section; int /*<<< orphan*/  vdr_length; int /*<<< orphan*/  vdr_section; TYPE_1__* entry; int /*<<< orphan*/  pdr_length; int /*<<< orphan*/  pdr_section; int /*<<< orphan*/  cd_length; int /*<<< orphan*/  cd_section; int /*<<< orphan*/  Configuration_Record_Length; int /*<<< orphan*/  Max_PD_Entries; int /*<<< orphan*/  Max_Primary_Element_Entries; int /*<<< orphan*/  Vendor_Specific_Logs_Length; int /*<<< orphan*/  Vendor_Specific_Logs; int /*<<< orphan*/  Diagnostic_Space_Length; int /*<<< orphan*/  Diagnostic_Space; int /*<<< orphan*/  Secondary_Header_LBA; int /*<<< orphan*/  Primary_Header_LBA; int /*<<< orphan*/  DDF_Header_GUID; int /*<<< orphan*/  CRC; } ;
typedef  int off_t ;
struct TYPE_14__ {int /*<<< orphan*/  Signature; } ;
struct TYPE_13__ {int /*<<< orphan*/  Signature; } ;
struct TYPE_12__ {int /*<<< orphan*/  PD_Reference; int /*<<< orphan*/  Signature; } ;
struct TYPE_11__ {TYPE_2__* entry; int /*<<< orphan*/  Populated_PDEs; int /*<<< orphan*/  Signature; } ;
struct TYPE_10__ {int /*<<< orphan*/  Signature; } ;
struct TYPE_9__ {int /*<<< orphan*/  Configured_Size; int /*<<< orphan*/  PD_State; int /*<<< orphan*/  PD_Reference; } ;
struct TYPE_8__ {int /*<<< orphan*/  PD_GUID; } ;

/* Variables and functions */
 int DDF_BBML_SIGNATURE ; 
 int DDF_CONTROLLER_DATA_SIGNATURE ; 
 scalar_t__ DDF_HEADER_ANCHOR ; 
 scalar_t__ DDF_HEADER_PRIMARY ; 
 scalar_t__ DDF_HEADER_SECONDARY ; 
 scalar_t__ DDF_HEADER_SIGNATURE ; 
 int DDF_PDD_SIGNATURE ; 
 int DDF_PDE_FAILED ; 
 int DDF_PDR_SIGNATURE ; 
 int DDF_VD_RECORD_SIGNATURE ; 
 int EINVAL ; 
 int GET16 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int GET32 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 unsigned long long GET64 (struct ddf_meta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*,char*,...) ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  M_MD_DDF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SET16 (struct ddf_meta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET32 (struct ddf_meta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET64 (struct ddf_meta*,int /*<<< orphan*/ ,unsigned long long) ; 
 TYPE_7__* bbm ; 
 scalar_t__ be32dec (scalar_t__*) ; 
 TYPE_6__* cdr ; 
 scalar_t__ crc32 (struct ddf_header*,int) ; 
 int ddf_meta_find_pd (struct ddf_meta*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ddf_meta_free (struct ddf_meta*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_read_data (struct g_consumer*,int,int,int*) ; 
 scalar_t__ isff (int /*<<< orphan*/ ,int) ; 
 scalar_t__ le32dec (scalar_t__*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max (int,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct ddf_header*,char*,int) ; 
 int min (int,int) ; 
 TYPE_5__* pdd ; 
 TYPE_4__* pdr ; 
 TYPE_3__* vdr ; 

__attribute__((used)) static int
ddf_meta_read(struct g_consumer *cp, struct ddf_meta *meta)
{
	struct g_provider *pp;
	struct ddf_header *ahdr, *hdr;
	char *abuf, *buf;
	off_t plba, slba, lba;
	int error, len, i;
	u_int ss;
	uint32_t val;

	ddf_meta_free(meta);
	pp = cp->provider;
	ss = meta->sectorsize = pp->sectorsize;
	/* Read anchor block. */
	abuf = g_read_data(cp, pp->mediasize - ss, ss, &error);
	if (abuf == NULL) {
		G_RAID_DEBUG(1, "Cannot read metadata from %s (error=%d).",
		    pp->name, error);
		return (error);
	}
	ahdr = (struct ddf_header *)abuf;

	/* Check if this is an DDF RAID struct */
	if (be32dec(&ahdr->Signature) == DDF_HEADER_SIGNATURE)
		meta->bigendian = 1;
	else if (le32dec(&ahdr->Signature) == DDF_HEADER_SIGNATURE)
		meta->bigendian = 0;
	else {
		G_RAID_DEBUG(1, "DDF signature check failed on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	if (ahdr->Header_Type != DDF_HEADER_ANCHOR) {
		G_RAID_DEBUG(1, "DDF header type check failed on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	meta->hdr = ahdr;
	plba = GET64(meta, hdr->Primary_Header_LBA);
	slba = GET64(meta, hdr->Secondary_Header_LBA);
	val = GET32(meta, hdr->CRC);
	SET32(meta, hdr->CRC, 0xffffffff);
	meta->hdr = NULL;
	if (crc32(ahdr, ss) != val) {
		G_RAID_DEBUG(1, "DDF CRC mismatch on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	if ((plba + 6) * ss >= pp->mediasize) {
		G_RAID_DEBUG(1, "DDF primary header LBA is wrong on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	if (slba != -1 && (slba + 6) * ss >= pp->mediasize) {
		G_RAID_DEBUG(1, "DDF secondary header LBA is wrong on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	lba = plba;

doread:
	error = 0;
	ddf_meta_free(meta);

	/* Read header block. */
	buf = g_read_data(cp, lba * ss, ss, &error);
	if (buf == NULL) {
readerror:
		G_RAID_DEBUG(1, "DDF %s metadata read error on %s (error=%d).",
		    (lba == plba) ? "primary" : "secondary", pp->name, error);
		if (lba == plba && slba != -1) {
			lba = slba;
			goto doread;
		}
		G_RAID_DEBUG(1, "DDF metadata read error on %s.", pp->name);
		goto done;
	}
	meta->hdr = malloc(ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->hdr, buf, ss);
	g_free(buf);
	hdr = meta->hdr;
	val = GET32(meta, hdr->CRC);
	SET32(meta, hdr->CRC, 0xffffffff);
	if (hdr->Signature != ahdr->Signature ||
	    crc32(meta->hdr, ss) != val ||
	    memcmp(hdr->DDF_Header_GUID, ahdr->DDF_Header_GUID, 24) ||
	    GET64(meta, hdr->Primary_Header_LBA) != plba ||
	    GET64(meta, hdr->Secondary_Header_LBA) != slba) {
hdrerror:
		G_RAID_DEBUG(1, "DDF %s metadata check failed on %s",
		    (lba == plba) ? "primary" : "secondary", pp->name);
		if (lba == plba && slba != -1) {
			lba = slba;
			goto doread;
		}
		G_RAID_DEBUG(1, "DDF metadata check failed on %s", pp->name);
		error = EINVAL;
		goto done;
	}
	if ((lba == plba && hdr->Header_Type != DDF_HEADER_PRIMARY) ||
	    (lba == slba && hdr->Header_Type != DDF_HEADER_SECONDARY))
		goto hdrerror;
	len = 1;
	len = max(len, GET32(meta, hdr->cd_section) + GET32(meta, hdr->cd_length));
	len = max(len, GET32(meta, hdr->pdr_section) + GET32(meta, hdr->pdr_length));
	len = max(len, GET32(meta, hdr->vdr_section) + GET32(meta, hdr->vdr_length));
	len = max(len, GET32(meta, hdr->cr_section) + GET32(meta, hdr->cr_length));
	len = max(len, GET32(meta, hdr->pdd_section) + GET32(meta, hdr->pdd_length));
	if ((val = GET32(meta, hdr->bbmlog_section)) != 0xffffffff)
		len = max(len, val + GET32(meta, hdr->bbmlog_length));
	if ((val = GET32(meta, hdr->Diagnostic_Space)) != 0xffffffff)
		len = max(len, val + GET32(meta, hdr->Diagnostic_Space_Length));
	if ((val = GET32(meta, hdr->Vendor_Specific_Logs)) != 0xffffffff)
		len = max(len, val + GET32(meta, hdr->Vendor_Specific_Logs_Length));
	if ((plba + len) * ss >= pp->mediasize)
		goto hdrerror;
	if (slba != -1 && (slba + len) * ss >= pp->mediasize)
		goto hdrerror;
	/* Workaround for Adaptec implementation. */
	if (GET16(meta, hdr->Max_Primary_Element_Entries) == 0xffff) {
		SET16(meta, hdr->Max_Primary_Element_Entries,
		    min(GET16(meta, hdr->Max_PD_Entries),
		    (GET16(meta, hdr->Configuration_Record_Length) * ss - 512) / 12));
	}

	if (GET32(meta, hdr->cd_length) * ss >= MAXPHYS ||
	    GET32(meta, hdr->pdr_length) * ss >= MAXPHYS ||
	    GET32(meta, hdr->vdr_length) * ss >= MAXPHYS ||
	    GET32(meta, hdr->cr_length) * ss >= MAXPHYS ||
	    GET32(meta, hdr->pdd_length) * ss >= MAXPHYS ||
	    GET32(meta, hdr->bbmlog_length) * ss >= MAXPHYS) {
		G_RAID_DEBUG(1, "%s: Blocksize is too big.", pp->name);
		goto hdrerror;
	}

	/* Read controller data. */
	buf = g_read_data(cp, (lba + GET32(meta, hdr->cd_section)) * ss,
	    GET32(meta, hdr->cd_length) * ss, &error);
	if (buf == NULL)
		goto readerror;
	meta->cdr = malloc(GET32(meta, hdr->cd_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->cdr, buf, GET32(meta, hdr->cd_length) * ss);
	g_free(buf);
	if (GET32(meta, cdr->Signature) != DDF_CONTROLLER_DATA_SIGNATURE)
		goto hdrerror;

	/* Read physical disk records. */
	buf = g_read_data(cp, (lba + GET32(meta, hdr->pdr_section)) * ss,
	    GET32(meta, hdr->pdr_length) * ss, &error);
	if (buf == NULL)
		goto readerror;
	meta->pdr = malloc(GET32(meta, hdr->pdr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->pdr, buf, GET32(meta, hdr->pdr_length) * ss);
	g_free(buf);
	if (GET32(meta, pdr->Signature) != DDF_PDR_SIGNATURE)
		goto hdrerror;
	/*
	 * Workaround for reading metadata corrupted due to graid bug.
	 * XXX: Remove this before we have disks above 128PB. :)
	 */
	if (meta->bigendian) {
		for (i = 0; i < GET16(meta, pdr->Populated_PDEs); i++) {
			if (isff(meta->pdr->entry[i].PD_GUID, 24))
				continue;
			if (GET32(meta, pdr->entry[i].PD_Reference) ==
			    0xffffffff)
				continue;
			if (GET64(meta, pdr->entry[i].Configured_Size) >=
			     (1ULL << 48)) {
				SET16(meta, pdr->entry[i].PD_State,
				    GET16(meta, pdr->entry[i].PD_State) &
				    ~DDF_PDE_FAILED);
				SET64(meta, pdr->entry[i].Configured_Size,
				    GET64(meta, pdr->entry[i].Configured_Size) &
				    ((1ULL << 48) - 1));
			}
		}
	}

	/* Read virtual disk records. */
	buf = g_read_data(cp, (lba + GET32(meta, hdr->vdr_section)) * ss,
	    GET32(meta, hdr->vdr_length) * ss, &error);
	if (buf == NULL)
		goto readerror;
	meta->vdr = malloc(GET32(meta, hdr->vdr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->vdr, buf, GET32(meta, hdr->vdr_length) * ss);
	g_free(buf);
	if (GET32(meta, vdr->Signature) != DDF_VD_RECORD_SIGNATURE)
		goto hdrerror;

	/* Read configuration records. */
	buf = g_read_data(cp, (lba + GET32(meta, hdr->cr_section)) * ss,
	    GET32(meta, hdr->cr_length) * ss, &error);
	if (buf == NULL)
		goto readerror;
	meta->cr = malloc(GET32(meta, hdr->cr_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->cr, buf, GET32(meta, hdr->cr_length) * ss);
	g_free(buf);

	/* Read physical disk data. */
	buf = g_read_data(cp, (lba + GET32(meta, hdr->pdd_section)) * ss,
	    GET32(meta, hdr->pdd_length) * ss, &error);
	if (buf == NULL)
		goto readerror;
	meta->pdd = malloc(GET32(meta, hdr->pdd_length) * ss, M_MD_DDF, M_WAITOK);
	memcpy(meta->pdd, buf, GET32(meta, hdr->pdd_length) * ss);
	g_free(buf);
	if (GET32(meta, pdd->Signature) != DDF_PDD_SIGNATURE)
		goto hdrerror;
	i = ddf_meta_find_pd(meta, NULL, GET32(meta, pdd->PD_Reference));
	if (i < 0)
		goto hdrerror;

	/* Read BBM Log. */
	if (GET32(meta, hdr->bbmlog_section) != 0xffffffff &&
	    GET32(meta, hdr->bbmlog_length) != 0) {
		buf = g_read_data(cp, (lba + GET32(meta, hdr->bbmlog_section)) * ss,
		    GET32(meta, hdr->bbmlog_length) * ss, &error);
		if (buf == NULL)
			goto readerror;
		meta->bbm = malloc(GET32(meta, hdr->bbmlog_length) * ss, M_MD_DDF, M_WAITOK);
		memcpy(meta->bbm, buf, GET32(meta, hdr->bbmlog_length) * ss);
		g_free(buf);
		if (GET32(meta, bbm->Signature) != DDF_BBML_SIGNATURE)
			goto hdrerror;
	}

done:
	g_free(abuf);
	if (error != 0)
		ddf_meta_free(meta);
	return (error);
}