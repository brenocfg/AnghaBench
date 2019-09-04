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
 int /*<<< orphan*/  _pico_copy_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_normal_is_unit_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pico_normal_within_tolerance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _pico_normals_assign_generated_normals(picoNormalIter_t first, picoNormalIter_t last, picoNormalIter_t generated) {
	for (; first != last; ++first, ++generated)
	{
		if (!_pico_normal_is_unit_length(*first) || !_pico_normal_within_tolerance(*first, *generated)) {
			_pico_copy_vec(*generated, *first);
		}
	}
}