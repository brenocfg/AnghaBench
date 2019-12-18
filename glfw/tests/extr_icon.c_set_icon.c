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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWimage ;

/* Variables and functions */
 int /*<<< orphan*/  glfwSetWindowIcon (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * icon_colors ; 
 int /*<<< orphan*/ ** logo ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_icon(GLFWwindow* window, int icon_color)
{
    int x, y;
    unsigned char pixels[16 * 16 * 4];
    unsigned char* target = pixels;
    GLFWimage img = { 16, 16, pixels };

    for (y = 0;  y < img.width;  y++)
    {
        for (x = 0;  x < img.height;  x++)
        {
            if (logo[y][x] == '0')
                memcpy(target, icon_colors[icon_color], 4);
            else
                memset(target, 0, 4);

            target += 4;
        }
    }

    glfwSetWindowIcon(window, 1, &img);
}