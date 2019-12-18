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
 float A_crossover ; 
 float B_crossover ; 
 int FLT_EPSILON ; 
 float FOUR_SQRT_MIN ; 
 float f (float,float,float) ; 
 int fabsf (float) ; 
 float hypotf (float,float) ; 
 float log1pf (float) ; 
 float logf (float) ; 
 float sqrtf (int) ; 

__attribute__((used)) static inline void
do_hard_work(float x, float y, float *rx, int *B_is_usable, float *B,
    float *sqrt_A2my2, float *new_y)
{
	float R, S, A;
	float Am1, Amy;

	R = hypotf(x, y + 1);
	S = hypotf(x, y - 1);

	A = (R + S) / 2;
	if (A < 1)
		A = 1;

	if (A < A_crossover) {
		if (y == 1 && x < FLT_EPSILON * FLT_EPSILON / 128) {
			*rx = sqrtf(x);
		} else if (x >= FLT_EPSILON * fabsf(y - 1)) {
			Am1 = f(x, 1 + y, R) + f(x, 1 - y, S);
			*rx = log1pf(Am1 + sqrtf(Am1 * (A + 1)));
		} else if (y < 1) {
			*rx = x / sqrtf((1 - y) * (1 + y));
		} else {
			*rx = log1pf((y - 1) + sqrtf((y - 1) * (y + 1)));
		}
	} else {
		*rx = logf(A + sqrtf(A * A - 1));
	}

	*new_y = y;

	if (y < FOUR_SQRT_MIN) {
		*B_is_usable = 0;
		*sqrt_A2my2 = A * (2 / FLT_EPSILON);
		*new_y = y * (2 / FLT_EPSILON);
		return;
	}

	*B = y / A;
	*B_is_usable = 1;

	if (*B > B_crossover) {
		*B_is_usable = 0;
		if (y == 1 && x < FLT_EPSILON / 128) {
			*sqrt_A2my2 = sqrtf(x) * sqrtf((A + y) / 2);
		} else if (x >= FLT_EPSILON * fabsf(y - 1)) {
			Amy = f(x, y + 1, R) + f(x, y - 1, S);
			*sqrt_A2my2 = sqrtf(Amy * (A + y));
		} else if (y > 1) {
			*sqrt_A2my2 = x * (4 / FLT_EPSILON / FLT_EPSILON) * y /
			    sqrtf((y + 1) * (y - 1));
			*new_y = y * (4 / FLT_EPSILON / FLT_EPSILON);
		} else {
			*sqrt_A2my2 = sqrtf((1 - y) * (1 + y));
		}
	}
}