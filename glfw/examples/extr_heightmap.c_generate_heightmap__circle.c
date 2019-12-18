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

/* Variables and functions */
 float DISPLACEMENT_SIGN_LIMIT ; 
 float MAP_SIZE ; 
 float MAX_CIRCLE_SIZE ; 
 float MAX_DISPLACEMENT ; 
 float RAND_MAX ; 
 float rand () ; 

__attribute__((used)) static void generate_heightmap__circle(float* center_x, float* center_y,
        float* size, float* displacement)
{
    float sign;
    /* random value for element in between [0-1.0] */
    *center_x = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
    *center_y = (MAP_SIZE * rand()) / (1.0f * RAND_MAX);
    *size = (MAX_CIRCLE_SIZE * rand()) / (1.0f * RAND_MAX);
    sign = (1.0f * rand()) / (1.0f * RAND_MAX);
    sign = (sign < DISPLACEMENT_SIGN_LIMIT) ? -1.0f : 1.0f;
    *displacement = (sign * (MAX_DISPLACEMENT * rand())) / (1.0f * RAND_MAX);
}