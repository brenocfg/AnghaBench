#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float x; float y; double r; float g; float b; scalar_t__ z; } ;
typedef  float GLfloat ;

/* Variables and functions */
 int GRIDH ; 
 int GRIDW ; 
 int QUADH ; 
 int QUADW ; 
 int* quad ; 
 TYPE_1__* vertex ; 

void init_vertices(void)
{
    int x, y, p;

    // Place the vertices in a grid
    for (y = 0;  y < GRIDH;  y++)
    {
        for (x = 0;  x < GRIDW;  x++)
        {
            p = y * GRIDW + x;

            vertex[p].x = (GLfloat) (x - GRIDW / 2) / (GLfloat) (GRIDW / 2);
            vertex[p].y = (GLfloat) (y - GRIDH / 2) / (GLfloat) (GRIDH / 2);
            vertex[p].z = 0;

            if ((x % 4 < 2) ^ (y % 4 < 2))
                vertex[p].r = 0.0;
            else
                vertex[p].r = 1.0;

            vertex[p].g = (GLfloat) y / (GLfloat) GRIDH;
            vertex[p].b = 1.f - ((GLfloat) x / (GLfloat) GRIDW + (GLfloat) y / (GLfloat) GRIDH) / 2.f;
        }
    }

    for (y = 0;  y < QUADH;  y++)
    {
        for (x = 0;  x < QUADW;  x++)
        {
            p = 4 * (y * QUADW + x);

            quad[p + 0] = y       * GRIDW + x;     // Some point
            quad[p + 1] = y       * GRIDW + x + 1; // Neighbor at the right side
            quad[p + 2] = (y + 1) * GRIDW + x + 1; // Upper right neighbor
            quad[p + 3] = (y + 1) * GRIDW + x;     // Upper neighbor
        }
    }
}