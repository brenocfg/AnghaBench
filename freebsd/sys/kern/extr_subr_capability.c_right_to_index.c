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
typedef  int /*<<< orphan*/  bit2idx ;

/* Variables and functions */
 int CAPIDXBIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static __inline int
right_to_index(uint64_t right)
{
	static const int bit2idx[] = {
		-1, 0, 1, -1, 2, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1, -1,
		4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
	};
	int idx;

	idx = CAPIDXBIT(right);
	assert(idx >= 0 && idx < sizeof(bit2idx) / sizeof(bit2idx[0]));
	return (bit2idx[idx]);
}