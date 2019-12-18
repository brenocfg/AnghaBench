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
typedef  int /*<<< orphan*/  vec_accu_t ;
typedef  int* vec3_accu_t ;

/* Variables and functions */
 int /*<<< orphan*/  sqrt (int) ; 

vec_accu_t VectorLengthAccu( const vec3_accu_t v ){
	return (vec_accu_t) sqrt( ( v[0] * v[0] ) + ( v[1] * v[1] ) + ( v[2] * v[2] ) );
}