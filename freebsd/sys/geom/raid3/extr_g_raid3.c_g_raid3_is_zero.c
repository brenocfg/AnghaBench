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
typedef  int /*<<< orphan*/  zeros ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct bio {scalar_t__ bio_length; scalar_t__ bio_data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
g_raid3_is_zero(struct bio *bp)
{
	static const uint64_t zeros[] = {
	    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	u_char *addr;
	ssize_t size;

	size = bp->bio_length;
	addr = (u_char *)bp->bio_data;
	for (; size > 0; size -= sizeof(zeros), addr += sizeof(zeros)) {
		if (bcmp(addr, zeros, sizeof(zeros)) != 0)
			return (0);
	}
	return (1);
}