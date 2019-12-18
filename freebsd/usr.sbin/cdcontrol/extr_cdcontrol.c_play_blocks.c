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
struct ioc_play_blocks {int blk; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDIOCPLAYBLOCKS ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ioc_play_blocks*) ; 

__attribute__((used)) static int
play_blocks(int blk, int len)
{
	struct ioc_play_blocks  t;

	t.blk = blk;
	t.len = len;

	return ioctl (fd, CDIOCPLAYBLOCKS, &t);
}