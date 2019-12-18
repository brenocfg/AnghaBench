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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  regmatch_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  _GLFWjoystick ;
struct TYPE_3__ {scalar_t__ inotify; int /*<<< orphan*/  regex; int /*<<< orphan*/  watch; } ;
struct TYPE_4__ {int /*<<< orphan*/  joysticks; TYPE_1__ linjs; } ;
typedef  int /*<<< orphan*/  GLFWbool ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int IN_ATTRIB ; 
 int IN_CLOEXEC ; 
 int IN_CREATE ; 
 int IN_DELETE ; 
 int IN_NONBLOCK ; 
 int PATH_MAX ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compareJoysticks ; 
 int /*<<< orphan*/  inotify_add_watch (scalar_t__,char const*,int) ; 
 scalar_t__ inotify_init1 (int) ; 
 scalar_t__ openJoystickDevice (char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 

GLFWbool _glfwInitJoysticksLinux(void)
{
    const char* dirname = "/dev/input";

    _glfw.linjs.inotify = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    if (_glfw.linjs.inotify > 0)
    {
        // HACK: Register for IN_ATTRIB to get notified when udev is done
        //       This works well in practice but the true way is libudev

        _glfw.linjs.watch = inotify_add_watch(_glfw.linjs.inotify,
                                              dirname,
                                              IN_CREATE | IN_ATTRIB | IN_DELETE);
    }

    // Continue without device connection notifications if inotify fails

    if (regcomp(&_glfw.linjs.regex, "^event[0-9]\\+$", 0) != 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Linux: Failed to compile regex");
        return GLFW_FALSE;
    }

    int count = 0;

    DIR* dir = opendir(dirname);
    if (dir)
    {
        struct dirent* entry;

        while ((entry = readdir(dir)))
        {
            regmatch_t match;

            if (regexec(&_glfw.linjs.regex, entry->d_name, 1, &match, 0) != 0)
                continue;

            char path[PATH_MAX];

            snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

            if (openJoystickDevice(path))
                count++;
        }

        closedir(dir);
    }

    // Continue with no joysticks if enumeration fails

    qsort(_glfw.joysticks, count, sizeof(_GLFWjoystick), compareJoysticks);
    return GLFW_TRUE;
}