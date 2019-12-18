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
typedef  int uint64_t ;
struct _region {int dummy; } ;
struct _citrus_mapper_std_rowcol_ext_ilseq_info_x {int /*<<< orphan*/  eix_dst_ilseq; int /*<<< orphan*/  eix_oob_mode; } ;
struct _citrus_mapper_std_rowcol {int rc_src_rowcol_bits; int rc_src_rowcol_len; int rc_dst_unit_bits; struct _region rc_table; struct _citrus_mapper_std_linear_zone* rc_src_rowcol; void* rc_dst_ilseq; void* rc_oob_mode; void* rc_dst_invalid; } ;
struct _citrus_mapper_std_linear_zone {int width; } ;
struct _citrus_mapper_std {int /*<<< orphan*/  ms_db; struct _citrus_mapper_std_rowcol ms_rowcol; int /*<<< orphan*/ * ms_uninit; int /*<<< orphan*/ * ms_convert; } ;

/* Variables and functions */
 int EFTYPE ; 
 int ENOENT ; 
 int UINT32_MAX ; 
 void* _CITRUS_MAPPER_STD_OOB_NONIDENTICAL ; 
#define  _CITRUS_MAPPER_STD_ROWCOL_INFO_COMPAT_SIZE 129 
#define  _CITRUS_MAPPER_STD_ROWCOL_INFO_SIZE 128 
 int /*<<< orphan*/  _CITRUS_MAPPER_STD_SYM_INFO ; 
 int /*<<< orphan*/  _CITRUS_MAPPER_STD_SYM_ROWCOL_EXT_ILSEQ ; 
 int /*<<< orphan*/  _CITRUS_MAPPER_STD_SYM_TABLE ; 
 int _db_lookup_by_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _region*,int /*<<< orphan*/ *) ; 
 struct _citrus_mapper_std_rowcol_ext_ilseq_info_x* _region_head (struct _region*) ; 
 int _region_size (struct _region*) ; 
 void* be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rowcol_convert ; 
 int rowcol_parse_variable (struct _citrus_mapper_std_rowcol*,struct _region*) ; 
 int rowcol_parse_variable_compat (struct _citrus_mapper_std_rowcol*,struct _region*) ; 
 int /*<<< orphan*/  rowcol_uninit ; 

__attribute__((used)) static int
rowcol_init(struct _citrus_mapper_std *ms)
{
	struct _citrus_mapper_std_linear_zone *lz;
	struct _citrus_mapper_std_rowcol *rc;
	const struct _citrus_mapper_std_rowcol_ext_ilseq_info_x *eix;
	struct _region r;
	uint64_t table_size;
	size_t i;
	int ret;

	ms->ms_convert = &rowcol_convert;
	ms->ms_uninit = &rowcol_uninit;
	rc = &ms->ms_rowcol;

	/* get table region */
	ret = _db_lookup_by_s(ms->ms_db, _CITRUS_MAPPER_STD_SYM_TABLE,
	    &rc->rc_table, NULL);
	if (ret) {
		if (ret == ENOENT)
			ret = EFTYPE;
		return (ret);
	}

	/* get table information */
	ret = _db_lookup_by_s(ms->ms_db, _CITRUS_MAPPER_STD_SYM_INFO, &r, NULL);
	if (ret) {
		if (ret == ENOENT)
			ret = EFTYPE;
		return (ret);
	}
	switch (_region_size(&r)) {
	case _CITRUS_MAPPER_STD_ROWCOL_INFO_COMPAT_SIZE:
		ret = rowcol_parse_variable_compat(rc, &r);
		break;
	case _CITRUS_MAPPER_STD_ROWCOL_INFO_SIZE:
		ret = rowcol_parse_variable(rc, &r);
		break;
	default:
		return (EFTYPE);
	}
	if (ret != 0)
		return (ret);
	/* sanity check */
	switch (rc->rc_src_rowcol_bits) {
	case 8: case 16: case 32:
		if (rc->rc_src_rowcol_len <= 32 / rc->rc_src_rowcol_bits)
			break;
	/*FALLTHROUGH*/
	default:
		return (EFTYPE);
	}

	/* ilseq extension */
	rc->rc_oob_mode = _CITRUS_MAPPER_STD_OOB_NONIDENTICAL;
	rc->rc_dst_ilseq = rc->rc_dst_invalid;
	ret = _db_lookup_by_s(ms->ms_db,
	    _CITRUS_MAPPER_STD_SYM_ROWCOL_EXT_ILSEQ, &r, NULL);
	if (ret && ret != ENOENT)
		return (ret);
	if (_region_size(&r) < sizeof(*eix))
		return (EFTYPE);
	if (ret == 0) {
		eix = _region_head(&r);
		rc->rc_oob_mode = be32toh(eix->eix_oob_mode);
		rc->rc_dst_ilseq = be32toh(eix->eix_dst_ilseq);
	}

	/* calcurate expected table size */
	i = rc->rc_src_rowcol_len;
	lz = &rc->rc_src_rowcol[--i];
	table_size = lz->width;
	while (i > 0) {
		lz = &rc->rc_src_rowcol[--i];
		table_size *= lz->width;
	}
	table_size *= rc->rc_dst_unit_bits/8;

	if (table_size > UINT32_MAX ||
	    _region_size(&rc->rc_table) < table_size)
		return (EFTYPE);

	return (0);
}