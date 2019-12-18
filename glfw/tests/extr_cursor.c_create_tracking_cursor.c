#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int member_1; unsigned char* member_2; int width; int height; } ;
typedef  TYPE_1__ GLFWimage ;
typedef  int /*<<< orphan*/  GLFWcursor ;

/* Variables and functions */
 int /*<<< orphan*/ * glfwCreateCursor (TYPE_1__ const*,int,int) ; 

__attribute__((used)) static GLFWcursor* create_tracking_cursor(void)
{
    int i = 0, x, y;
    unsigned char buffer[32 * 32 * 4];
    const GLFWimage image = { 32, 32, buffer };

    for (y = 0;  y < image.width;  y++)
    {
        for (x = 0;  x < image.height;  x++)
        {
            if (x == 7 || y == 7)
            {
                buffer[i++] = 255;
                buffer[i++] = 0;
                buffer[i++] = 0;
                buffer[i++] = 255;
            }
            else
            {
                buffer[i++] = 0;
                buffer[i++] = 0;
                buffer[i++] = 0;
                buffer[i++] = 0;
            }
        }
    }

    return glfwCreateCursor(&image, 7, 7);
}