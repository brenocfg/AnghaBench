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
typedef  int uint32_t ;
struct devdesc {int /*<<< orphan*/  d_unit; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ host_llseek (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int host_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
hostdisk_strategy(void *devdata, int flag, daddr_t dblk, size_t size,
    char *buf, size_t *rsize)
{
	struct devdesc *desc = devdata;
	daddr_t pos;
	int n;
	uint64_t res;
	uint32_t posl, posh;

	pos = dblk * 512;

	posl = pos & 0xffffffff;
	posh = (pos >> 32) & 0xffffffff;
	if (host_llseek(desc->d_unit, posh, posl, &res, 0) < 0) {
		printf("Seek error\n");
		return (EIO);
	}
	n = host_read(desc->d_unit, buf, size);

	if (n < 0)
		return (EIO);

	*rsize = n;
	return (0);
}