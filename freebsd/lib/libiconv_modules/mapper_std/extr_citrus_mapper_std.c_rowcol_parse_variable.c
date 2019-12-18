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
typedef  int uint32_t ;
struct _region {int dummy; } ;
struct _citrus_mapper_std_rowcol_info_x {TYPE_1__* rcx_src_rowcol; int /*<<< orphan*/  rcx_src_rowcol_len; int /*<<< orphan*/  rcx_src_rowcol_bits; int /*<<< orphan*/  rcx_dst_unit_bits; int /*<<< orphan*/  rcx_dst_invalid; } ;
struct _citrus_mapper_std_rowcol {int rc_src_rowcol_bits; int rc_src_rowcol_mask; int rc_src_rowcol_len; struct _citrus_mapper_std_linear_zone* rc_src_rowcol; void* rc_dst_unit_bits; void* rc_dst_invalid; } ;
struct _citrus_mapper_std_linear_zone {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int EFTYPE ; 
 int ENOMEM ; 
 int _CITRUS_MAPPER_STD_ROWCOL_MAX ; 
 struct _citrus_mapper_std_rowcol_info_x* _region_head (struct _region*) ; 
 void* be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct _citrus_mapper_std_linear_zone*) ; 
 struct _citrus_mapper_std_linear_zone* malloc (int) ; 
 int set_linear_zone (struct _citrus_mapper_std_linear_zone*,int,int) ; 

__attribute__((used)) static __inline int
rowcol_parse_variable(struct _citrus_mapper_std_rowcol *rc,
    struct _region *r)
{
	const struct _citrus_mapper_std_rowcol_info_x *rcx;
	struct _citrus_mapper_std_linear_zone *lz;
	size_t i;
	uint32_t m, n;
	int ret;

	rcx = _region_head(r);

	rc->rc_dst_invalid = be32toh(rcx->rcx_dst_invalid);
	rc->rc_dst_unit_bits = be32toh(rcx->rcx_dst_unit_bits);

	m = be32toh(rcx->rcx_src_rowcol_bits);
	n = 1 << (m - 1);
	n |= n - 1;
	rc->rc_src_rowcol_bits = m;
	rc->rc_src_rowcol_mask = n;

	rc->rc_src_rowcol_len = be32toh(rcx->rcx_src_rowcol_len);
	if (rc->rc_src_rowcol_len > _CITRUS_MAPPER_STD_ROWCOL_MAX)
		return (EFTYPE);
	rc->rc_src_rowcol = malloc(rc->rc_src_rowcol_len *
	    sizeof(*rc->rc_src_rowcol));
	if (rc->rc_src_rowcol == NULL)
		return (ENOMEM);
	for (i = 0, lz = rc->rc_src_rowcol;
	    i < rc->rc_src_rowcol_len; ++i, ++lz) {
		m = be32toh(rcx->rcx_src_rowcol[i].begin),
		n = be32toh(rcx->rcx_src_rowcol[i].end);
		ret = set_linear_zone(lz, m, n);
		if (ret != 0) {
			free(rc->rc_src_rowcol);
			rc->rc_src_rowcol = NULL;
			return (ret);
		}
	}
	return (0);
}