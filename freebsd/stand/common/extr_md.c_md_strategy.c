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
struct devdesc {scalar_t__ d_unit; } ;
typedef  size_t daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENXIO ; 
 int F_MASK ; 
#define  F_READ 129 
#define  F_WRITE 128 
 size_t MD_BLOCK_SIZE ; 
 size_t MD_IMAGE_SIZE ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 TYPE_1__ md_image ; 

__attribute__((used)) static int
md_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
	struct devdesc *dev = (struct devdesc *)devdata;
	size_t ofs;

	if (dev->d_unit != 0)
		return (ENXIO);

	if (blk < 0 || blk >= (MD_IMAGE_SIZE / MD_BLOCK_SIZE))
		return (EIO);

	if (size % MD_BLOCK_SIZE)
		return (EIO);

	ofs = blk * MD_BLOCK_SIZE;
	if ((ofs + size) > MD_IMAGE_SIZE)
		size = MD_IMAGE_SIZE - ofs;

	if (rsize != NULL)
		*rsize = size;

	switch (rw & F_MASK) {
	case F_READ:
		bcopy(md_image.start + ofs, buf, size);
		return (0);
	case F_WRITE:
		bcopy(buf, md_image.start + ofs, size);
		return (0);
	}

	return (ENODEV);
}