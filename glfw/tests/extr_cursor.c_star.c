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
 float M_PI ; 
 scalar_t__ fabs (int) ; 
 scalar_t__ fmax (float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmin (float,float const) ; 
 scalar_t__ sin (float) ; 
 scalar_t__ sqrt (int) ; 

__attribute__((used)) static float star(int x, int y, float t)
{
    const float c = 64 / 2.f;

    const float i = (0.25f * (float) sin(2.f * M_PI * t) + 0.75f);
    const float k = 64 * 0.046875f * i;

    const float dist = (float) sqrt((x - c) * (x - c) + (y - c) * (y - c));

    const float salpha = 1.f - dist / c;
    const float xalpha = (float) x == c ? c : k / (float) fabs(x - c);
    const float yalpha = (float) y == c ? c : k / (float) fabs(y - c);

    return (float) fmax(0.f, fmin(1.f, i * salpha * 0.2f + salpha * xalpha * yalpha));
}