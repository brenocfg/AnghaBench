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
struct TYPE_3__ {size_t clipboardSize; char* clipboardString; int /*<<< orphan*/  dataOffer; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  growClipboardString () ; 
 int /*<<< orphan*/  handleEvents (int) ; 
 int pipe2 (int*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  wl_data_offer_receive (int /*<<< orphan*/ ,char*,int) ; 

const char* _glfwPlatformGetClipboardString(void)
{
    int fds[2];
    int ret;
    size_t len = 0;

    if (!_glfw.wl.dataOffer)
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "No clipboard data has been sent yet");
        return NULL;
    }

    ret = pipe2(fds, O_CLOEXEC);
    if (ret < 0)
    {
        // TODO: also report errno maybe?
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Impossible to create clipboard pipe fds");
        return NULL;
    }

    wl_data_offer_receive(_glfw.wl.dataOffer, "text/plain;charset=utf-8", fds[1]);
    close(fds[1]);

    // XXX: this is a huge hack, this function shouldn’t be synchronous!
    handleEvents(-1);

    while (1)
    {
        // Grow the clipboard if we need to paste something bigger, there is no
        // shrink operation yet.
        if (len + 4096 > _glfw.wl.clipboardSize)
        {
            if (!growClipboardString())
            {
                close(fds[0]);
                return NULL;
            }
        }

        // Then read from the fd to the clipboard, handling all known errors.
        ret = read(fds[0], _glfw.wl.clipboardString + len, 4096);
        if (ret == 0)
            break;
        if (ret == -1 && errno == EINTR)
            continue;
        if (ret == -1)
        {
            // TODO: also report errno maybe.
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Impossible to read from clipboard fd");
            close(fds[0]);
            return NULL;
        }
        len += ret;
    }
    close(fds[0]);
    if (len + 1 > _glfw.wl.clipboardSize)
    {
        if (!growClipboardString())
            return NULL;
    }
    _glfw.wl.clipboardString[len] = '\0';
    return _glfw.wl.clipboardString;
}