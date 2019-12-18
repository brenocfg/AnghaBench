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
typedef  int /*<<< orphan*/ * picoNormalIter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_zero_vec (int /*<<< orphan*/ ) ; 

void _pico_normals_zero(picoNormalIter_t first, picoNormalIter_t last) {
	for (; first != last; ++first)
	{
		_pico_zero_vec(*first);
	}
}