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
typedef  float* picoVec3_t ;
typedef  size_t* picoIndexIter_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_add_vec (float*,float*,float*) ; 
 int /*<<< orphan*/  _pico_cross_vec (float*,float*,float*) ; 
 int /*<<< orphan*/  _pico_subtract_vec (float*,float*,float*) ; 

void _pico_triangles_generate_weighted_normals(picoIndexIter_t first, picoIndexIter_t end, picoVec3_t* xyz, picoVec3_t* normals) {
	for (; first != end; first += 3)
	{
#if (THE_CROSSPRODUCTS_OF_ANY_PAIR_OF_EDGES_OF_A_GIVEN_TRIANGLE_ARE_EQUAL)
		picoVec3_t weightedNormal;
		{
			float* a = xyz[*(first + 0)];
			float* b = xyz[*(first + 1)];
			float* c = xyz[*(first + 2)];
			picoVec3_t ba, ca;
			_pico_subtract_vec(b, a, ba);
			_pico_subtract_vec(c, a, ca);
			_pico_cross_vec(ca, ba, weightedNormal);
		}
#endif
		{
			int j = 0;
			for (; j < 3; ++j)
			{
				float* normal = normals[*(first + j)];
#if ( !THE_CROSSPRODUCTS_OF_ANY_PAIR_OF_EDGES_OF_A_GIVEN_TRIANGLE_ARE_EQUAL )
				picoVec3_t weightedNormal;
				{
					float* a = xyz[*(first + ((j + 0) % 3))];
					float* b = xyz[*(first + ((j + 1) % 3))];
					float* c = xyz[*(first + ((j + 2) % 3))];
					picoVec3_t ba, ca;
					_pico_subtract_vec(b, a, ba);
					_pico_subtract_vec(c, a, ca);
					_pico_cross_vec(ca, ba, weightedNormal);
				}
#endif
				_pico_add_vec(weightedNormal, normal, normal);
			}
		}
	}
}