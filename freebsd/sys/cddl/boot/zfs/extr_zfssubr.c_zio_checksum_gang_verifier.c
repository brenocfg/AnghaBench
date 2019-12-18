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
typedef  int /*<<< orphan*/  zio_cksum_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dva_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BP_IDENTITY (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_IS_GANG (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_PHYSICAL_BIRTH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zio_checksum_gang_verifier(zio_cksum_t *zcp, const blkptr_t *bp)
{
	const dva_t *dva = BP_IDENTITY(bp);
	uint64_t txg = BP_PHYSICAL_BIRTH(bp);

	ASSERT(BP_IS_GANG(bp));

	ZIO_SET_CHECKSUM(zcp, DVA_GET_VDEV(dva), DVA_GET_OFFSET(dva), txg, 0);
}