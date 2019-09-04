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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwapElements (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorInverse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorRotate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ qtrue ; 

void InverseRotation(const vec3_t angles, vec3_t point, qboolean right_handed) {
	vec3_t matrix[3];
	vec3_t tvec;
	AngleVectors(angles, matrix[0], matrix[1], matrix[2]);
	if ( right_handed == qtrue ) VectorInverse(matrix[1]);
	// Transpose matrix.
	SwapElements(matrix, 0, 1);
	SwapElements(matrix, 0, 2);
	SwapElements(matrix, 1, 2);
	// Copy point because VectorRotate requires for the input and output vectors
	// not to be aliases.
	VectorCopy(point, tvec);
	VectorRotate(tvec, matrix, point);
}