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

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 

__attribute__((used)) static __inline bool
hn_rndis_check_overlap(int off, int len, int check_off, int check_len)
{

	if (off < check_off) {
		if (__predict_true(off + len <= check_off))
			return (false);
	} else if (off > check_off) {
		if (__predict_true(check_off + check_len <= off))
			return (false);
	}
	return (true);
}