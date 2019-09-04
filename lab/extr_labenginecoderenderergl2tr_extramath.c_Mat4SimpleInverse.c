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
typedef  float* vec3_t ;
typedef  float* mat4_t ;

/* Variables and functions */
 float DotProduct (float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float* const,float*) ; 
 int /*<<< orphan*/  VectorScale (float*,float,float*) ; 

void Mat4SimpleInverse( const mat4_t in, mat4_t out)
{
	vec3_t v;
	float invSqrLen;
 
	VectorCopy(in + 0, v);
	invSqrLen = 1.0f / DotProduct(v, v); VectorScale(v, invSqrLen, v);
	out[ 0] = v[0]; out[ 4] = v[1]; out[ 8] = v[2]; out[12] = -DotProduct(v, &in[12]);

	VectorCopy(in + 4, v);
	invSqrLen = 1.0f / DotProduct(v, v); VectorScale(v, invSqrLen, v);
	out[ 1] = v[0]; out[ 5] = v[1]; out[ 9] = v[2]; out[13] = -DotProduct(v, &in[12]);

	VectorCopy(in + 8, v);
	invSqrLen = 1.0f / DotProduct(v, v); VectorScale(v, invSqrLen, v);
	out[ 2] = v[0]; out[ 6] = v[1]; out[10] = v[2]; out[14] = -DotProduct(v, &in[12]);

	out[ 3] = 0.0f; out[ 7] = 0.0f; out[11] = 0.0f; out[15] = 1.0f;
}