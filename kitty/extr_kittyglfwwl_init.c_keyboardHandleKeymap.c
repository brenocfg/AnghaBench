#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xkb; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  glfw_xkb_compile_keymap (int /*<<< orphan*/ *,char*) ; 
 char* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,scalar_t__) ; 

__attribute__((used)) static void keyboardHandleKeymap(void* data,
                                 struct wl_keyboard* keyboard,
                                 uint32_t format,
                                 int fd,
                                 uint32_t size)
{
    char* mapStr;

    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
    {
        close(fd);
        return;
    }

    mapStr = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (mapStr == MAP_FAILED) {
        close(fd);
        return;
    }
    glfw_xkb_compile_keymap(&_glfw.wl.xkb, mapStr);
    munmap(mapStr, size);
    close(fd);

}