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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_long ;
typedef  int u_int ;
struct open_file {struct ofw_devdesc* f_devdata; } ;
struct ofw_devdesc {int /*<<< orphan*/  d_handle; } ;

/* Variables and functions */
#define  DIOCGMEDIASIZE 129 
#define  DIOCGSECTORSIZE 128 
 int ENOTTY ; 
 int OF_block_size (int /*<<< orphan*/ ) ; 
 unsigned int OF_blocks (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ofwd_ioctl(struct open_file *f, u_long cmd, void *data)
{
	struct ofw_devdesc *dev = f->f_devdata;
	int block_size;
	unsigned int n;

	switch (cmd) {
	case DIOCGSECTORSIZE:
		block_size = OF_block_size(dev->d_handle);
		*(u_int *)data = block_size;
		break;
	case DIOCGMEDIASIZE:
		block_size = OF_block_size(dev->d_handle);
		n = OF_blocks(dev->d_handle);
		*(uint64_t *)data = (uint64_t)(n * block_size);
		break;
	default:
		return (ENOTTY);
	}
	return (0);
}