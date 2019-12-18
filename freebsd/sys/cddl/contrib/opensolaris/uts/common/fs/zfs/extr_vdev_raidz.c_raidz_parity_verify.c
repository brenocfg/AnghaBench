#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int zp_checksum; } ;
struct TYPE_11__ {TYPE_1__ io_prop; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_12__ {int rm_firstdatacol; TYPE_4__* rm_col; } ;
typedef  TYPE_3__ raidz_map_t ;
struct TYPE_13__ {scalar_t__ rc_error; int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_abd; int /*<<< orphan*/  rc_tried; } ;
typedef  TYPE_4__ raidz_col_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int BP_GET_CHECKSUM (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_IS_GANG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECKSUM ; 
 scalar_t__ SET_ERROR (int /*<<< orphan*/ ) ; 
 int VDEV_RAIDZ_MAXPARITY ; 
 int ZIO_CHECKSUM_GANG_HEADER ; 
 int ZIO_CHECKSUM_NOPARITY ; 
 scalar_t__ abd_cmp_buf (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_to_buf (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raidz_checksum_error (TYPE_2__*,TYPE_4__*,void*) ; 
 int /*<<< orphan*/  vdev_raidz_generate_parity (TYPE_3__*) ; 
 void* zio_buf_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_buf_free (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
raidz_parity_verify(zio_t *zio, raidz_map_t *rm)
{
	void *orig[VDEV_RAIDZ_MAXPARITY];
	int c, ret = 0;
	raidz_col_t *rc;

	blkptr_t *bp = zio->io_bp;
	enum zio_checksum checksum = (bp == NULL ? zio->io_prop.zp_checksum :
	    (BP_IS_GANG(bp) ? ZIO_CHECKSUM_GANG_HEADER : BP_GET_CHECKSUM(bp)));

	if (checksum == ZIO_CHECKSUM_NOPARITY)
		return (ret);

	for (c = 0; c < rm->rm_firstdatacol; c++) {
		rc = &rm->rm_col[c];
		if (!rc->rc_tried || rc->rc_error != 0)
			continue;
		orig[c] = zio_buf_alloc(rc->rc_size);
		abd_copy_to_buf(orig[c], rc->rc_abd, rc->rc_size);
	}

	vdev_raidz_generate_parity(rm);

	for (c = 0; c < rm->rm_firstdatacol; c++) {
		rc = &rm->rm_col[c];
		if (!rc->rc_tried || rc->rc_error != 0)
			continue;
		if (abd_cmp_buf(rc->rc_abd, orig[c], rc->rc_size) != 0) {
			raidz_checksum_error(zio, rc, orig[c]);
			rc->rc_error = SET_ERROR(ECKSUM);
			ret++;
		}
		zio_buf_free(orig[c], rc->rc_size);
	}

	return (ret);
}