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
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  m4x4_t ;

/* Variables and functions */
 int /*<<< orphan*/  m4x4_multiply_by_m4x4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m4x4_rotation_for_quat (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

void m4x4_rotate_by_quat( m4x4_t matrix, const vec4_t rotation ){
	m4x4_t temp;
	m4x4_rotation_for_quat( temp, rotation );
	m4x4_multiply_by_m4x4( matrix, temp );
}