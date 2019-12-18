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
typedef  int /*<<< orphan*/  picoVec_t ;
typedef  int /*<<< orphan*/ * picoVec4_t ;
typedef  int /*<<< orphan*/  picoVec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_cross_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pico_dot_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pico_normalize_vec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pico_subtract_vec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

picoVec_t _pico_calc_plane( picoVec4_t plane, picoVec3_t a, picoVec3_t b, picoVec3_t c ){
	picoVec3_t ba, ca;

	_pico_subtract_vec( b, a, ba );
	_pico_subtract_vec( c, a, ca );
	_pico_cross_vec( ca, ba, plane );
	plane[ 3 ] = _pico_dot_vec( a, plane );
	return _pico_normalize_vec( plane );
}