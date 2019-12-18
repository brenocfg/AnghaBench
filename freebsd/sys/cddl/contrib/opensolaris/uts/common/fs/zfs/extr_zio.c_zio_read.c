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
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  zio_priority_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_PHYSICAL_BIRTH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZIO_DDT_CHILD_READ_PIPELINE ; 
 int ZIO_FLAG_DDT_CHILD ; 
 int /*<<< orphan*/  ZIO_READ_PIPELINE ; 
 int /*<<< orphan*/  ZIO_STAGE_OPEN ; 
 int /*<<< orphan*/  ZIO_TYPE_READ ; 
 int /*<<< orphan*/  zfs_blkptr_verify (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * zio_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zio_t *
zio_read(zio_t *pio, spa_t *spa, const blkptr_t *bp,
    abd_t *data, uint64_t size, zio_done_func_t *done, void *private,
    zio_priority_t priority, enum zio_flag flags, const zbookmark_phys_t *zb)
{
	zio_t *zio;

	zfs_blkptr_verify(spa, bp);

	zio = zio_create(pio, spa, BP_PHYSICAL_BIRTH(bp), bp,
	    data, size, size, done, private,
	    ZIO_TYPE_READ, priority, flags, NULL, 0, zb,
	    ZIO_STAGE_OPEN, (flags & ZIO_FLAG_DDT_CHILD) ?
	    ZIO_DDT_CHILD_READ_PIPELINE : ZIO_READ_PIPELINE);

	return (zio);
}