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
typedef  scalar_t__* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int MAX_MAP_BOUNDS ; 
 int VERTEXHASH_SHIFT ; 
 int VERTEXHASH_SIZE ; 

unsigned TH_HashVec(vec3_t vec)
{
	int x, y;

	x = (MAX_MAP_BOUNDS + (int)(vec[0]+0.5)) >> VERTEXHASH_SHIFT;
	y = (MAX_MAP_BOUNDS + (int)(vec[1]+0.5)) >> VERTEXHASH_SHIFT;

	if (x < 0 || x >= VERTEXHASH_SIZE || y < 0 || y >= VERTEXHASH_SIZE)
		Error("HashVec: point %f %f %f outside valid range", vec[0], vec[1], vec[2]);
	
	return y*VERTEXHASH_SIZE + x;
}