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
typedef  unsigned int uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_BLOCK ; 
 int GXEMUL_DISK_DEV_BLOCKSIZE ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_DISKID ; 
 void* GXEMUL_DISK_DEV_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_OFFSET ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_OFFSET_HI ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_OFFSET_LO ; 
 int GXEMUL_DISK_DEV_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_START ; 
 unsigned int GXEMUL_DISK_DEV_START_WRITE ; 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_STATUS ; 
#define  GXEMUL_DISK_DEV_STATUS_FAILURE 128 
 int /*<<< orphan*/  GXEMUL_DISK_DEV_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  gxemul_disk_controller_mutex ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gxemul_disk_write(unsigned diskid, const void *buf, off_t off)
{
	volatile void *dst;

	mtx_assert(&gxemul_disk_controller_mutex, MA_OWNED);

	if (off < 0 || off % GXEMUL_DISK_DEV_BLOCKSIZE != 0)
		return (EINVAL);

#ifdef _LP64
	GXEMUL_DISK_DEV_WRITE(GXEMUL_DISK_DEV_OFFSET, (uint64_t)off);
#else
	GXEMUL_DISK_DEV_WRITE(GXEMUL_DISK_DEV_OFFSET_LO,
	    (uint32_t)(off & 0xffffffff));
	GXEMUL_DISK_DEV_WRITE(GXEMUL_DISK_DEV_OFFSET_HI,
	    (uint32_t)((off >> 32) & 0xffffffff));
#endif

	GXEMUL_DISK_DEV_WRITE(GXEMUL_DISK_DEV_DISKID, diskid);

	dst = GXEMUL_DISK_DEV_FUNCTION(GXEMUL_DISK_DEV_BLOCK);
	memcpy((void *)(uintptr_t)dst, buf, GXEMUL_DISK_DEV_BLOCKSIZE);

	GXEMUL_DISK_DEV_WRITE(GXEMUL_DISK_DEV_START, GXEMUL_DISK_DEV_START_WRITE);
	switch (GXEMUL_DISK_DEV_READ(GXEMUL_DISK_DEV_STATUS)) {
	case GXEMUL_DISK_DEV_STATUS_FAILURE:
		return (EIO);
	default:
		break;
	}

	return (0);
}