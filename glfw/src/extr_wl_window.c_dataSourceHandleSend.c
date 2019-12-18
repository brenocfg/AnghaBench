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
struct wl_data_source {int dummy; } ;
struct TYPE_3__ {char* clipboardSendString; size_t clipboardSendSize; struct wl_data_source* dataSource; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int write (int,char const*,size_t) ; 

__attribute__((used)) static void dataSourceHandleSend(void* data,
                                 struct wl_data_source* dataSource,
                                 const char* mimeType,
                                 int fd)
{
    const char* string = _glfw.wl.clipboardSendString;
    size_t len = _glfw.wl.clipboardSendSize;
    int ret;

    if (_glfw.wl.dataSource != dataSource)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Unknown clipboard data source");
        return;
    }

    if (!string)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Copy requested from an invalid string");
        return;
    }

    if (strcmp(mimeType, "text/plain;charset=utf-8") != 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Wrong MIME type asked from clipboard");
        close(fd);
        return;
    }

    while (len > 0)
    {
        ret = write(fd, string, len);
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret == -1)
        {
            // TODO: also report errno maybe.
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Error while writing the clipboard");
            close(fd);
            return;
        }
        len -= ret;
    }
    close(fd);
}