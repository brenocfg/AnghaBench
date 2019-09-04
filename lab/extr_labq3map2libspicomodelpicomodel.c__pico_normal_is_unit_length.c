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
typedef  int /*<<< orphan*/  picoVec3_t ;

/* Variables and functions */
 int FLOAT_EQUAL_EPSILON (int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORMAL_UNIT_LENGTH_EPSILON ; 
 int /*<<< orphan*/  _pico_length_vec (int /*<<< orphan*/ ) ; 

int _pico_normal_is_unit_length(picoVec3_t normal) {
	return FLOAT_EQUAL_EPSILON(_pico_length_vec(normal), 1.0, NORMAL_UNIT_LENGTH_EPSILON);
}