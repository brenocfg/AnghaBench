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
typedef  float vec_t ;
typedef  int /*<<< orphan*/  const vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 float DotProduct (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/  const,float,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/  const) ; 

vec_t R_CalcTangentSpace(vec3_t tangent, vec3_t bitangent, const vec3_t normal, const vec3_t sdir, const vec3_t tdir)
{
	vec3_t n_cross_t;
	vec_t n_dot_t, handedness;

	// Gram-Schmidt orthogonalize
	n_dot_t = DotProduct(normal, sdir);
	VectorMA(sdir, -n_dot_t, normal, tangent);
	VectorNormalize(tangent);

	// Calculate handedness
	CrossProduct(normal, sdir, n_cross_t);
	handedness = (DotProduct(n_cross_t, tdir) < 0.0f) ? -1.0f : 1.0f;

	// Calculate orthogonal bitangent, if necessary
	if (bitangent)
		CrossProduct(normal, tangent, bitangent);

	return handedness;
}