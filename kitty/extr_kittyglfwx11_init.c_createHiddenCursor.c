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
struct TYPE_3__ {int member_0; int member_1; unsigned char* member_2; } ;
typedef  TYPE_1__ GLFWimage ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwCreateCursorX11 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Cursor createHiddenCursor(void)
{
    unsigned char pixels[16 * 16 * 4] = { 0 };
    GLFWimage image = { 16, 16, pixels };
    return _glfwCreateCursorX11(&image, 0, 0);
}