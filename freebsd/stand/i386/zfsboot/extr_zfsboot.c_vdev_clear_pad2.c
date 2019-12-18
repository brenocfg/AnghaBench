#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  v_read_priv; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EIO ; 
 int VDEV_PAD_SIZE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 scalar_t__ vdev_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vl_pad2 ; 
 char* zap_scratch ; 

__attribute__((used)) static int
vdev_clear_pad2(vdev_t *vdev)
{
	char *zeroes = zap_scratch;
	uint64_t *end;
	off_t off = offsetof(vdev_label_t, vl_pad2);

	memset(zeroes, 0, VDEV_PAD_SIZE);
	end = (uint64_t *)(zeroes + VDEV_PAD_SIZE);
	/* ZIO_CHECKSUM_LABEL magic and pre-calcualted checksum for all zeros */
	end[-5] = 0x0210da7ab10c7a11;
	end[-4] = 0x97f48f807f6e2a3f;
	end[-3] = 0xaf909f1658aacefc;
	end[-2] = 0xcbd1ea57ff6db48b;
	end[-1] = 0x6ec692db0d465fab;
	if (vdev_write(vdev, vdev->v_read_priv, off, zeroes, VDEV_PAD_SIZE))
		return (EIO);
	return (0);
}