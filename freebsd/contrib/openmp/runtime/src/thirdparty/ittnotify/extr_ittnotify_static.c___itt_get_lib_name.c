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
typedef  int ssize_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITT_ANDROID_LOGE (char*,...) ; 
 int /*<<< orphan*/  ITT_ANDROID_LOGI (char*,...) ; 
 int /*<<< orphan*/  ITT_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIB_VAR_NAME ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 char* __itt_get_env_var (int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int getpid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int setenv (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static const char* __itt_get_lib_name(void)
{
    const char* lib_name = __itt_get_env_var(ITT_TO_STR(LIB_VAR_NAME));

#ifdef __ANDROID__
    if (lib_name == NULL)
    {

#if ITT_ARCH==ITT_ARCH_IA32 || ITT_ARCH==ITT_ARCH_ARM
        const char* const marker_filename = "com.intel.itt.collector_lib_32";
#else
        const char* const marker_filename = "com.intel.itt.collector_lib_64";
#endif

        char system_wide_marker_filename[PATH_MAX] = {0};
        int itt_marker_file_fd = -1;
        ssize_t res = 0;

        res = snprintf(system_wide_marker_filename, PATH_MAX - 1, "%s%s", "/data/local/tmp/", marker_filename);
        if (res < 0)
        {
            ITT_ANDROID_LOGE("Unable to concatenate marker file string.");
            return lib_name;
        }
        itt_marker_file_fd = open(system_wide_marker_filename, O_RDONLY);

        if (itt_marker_file_fd == -1)
        {
            const pid_t my_pid = getpid();
            char cmdline_path[PATH_MAX] = {0};
            char package_name[PATH_MAX] = {0};
            char app_sandbox_file[PATH_MAX] = {0};
            int cmdline_fd = 0;

            ITT_ANDROID_LOGI("Unable to open system-wide marker file.");
            res = snprintf(cmdline_path, PATH_MAX - 1, "/proc/%d/cmdline", my_pid);
            if (res < 0)
            {
                ITT_ANDROID_LOGE("Unable to get cmdline path string.");
                return lib_name;
            }

            ITT_ANDROID_LOGI("CMD file: %s\n", cmdline_path);
            cmdline_fd = open(cmdline_path, O_RDONLY);
            if (cmdline_fd == -1)
            {
                ITT_ANDROID_LOGE("Unable to open %s file!", cmdline_path);
                return lib_name;
            }
            res = read(cmdline_fd, package_name, PATH_MAX - 1);
            if (res == -1)
            {
                ITT_ANDROID_LOGE("Unable to read %s file!", cmdline_path);
                res = close(cmdline_fd);
                if (res == -1)
                {
                    ITT_ANDROID_LOGE("Unable to close %s file!", cmdline_path);
                }
                return lib_name;
            }
            res = close(cmdline_fd);
            if (res == -1)
            {
                ITT_ANDROID_LOGE("Unable to close %s file!", cmdline_path);
                return lib_name;
            }
            ITT_ANDROID_LOGI("Package name: %s\n", package_name);
            res = snprintf(app_sandbox_file, PATH_MAX - 1, "/data/data/%s/%s", package_name, marker_filename);
            if (res < 0)
            {
                ITT_ANDROID_LOGE("Unable to concatenate marker file string.");
                return lib_name;
            }

            ITT_ANDROID_LOGI("Lib marker file name: %s\n", app_sandbox_file);
            itt_marker_file_fd = open(app_sandbox_file, O_RDONLY);
            if (itt_marker_file_fd == -1)
            {
                ITT_ANDROID_LOGE("Unable to open app marker file!");
                return lib_name;
            }
        }

        {
            char itt_lib_name[PATH_MAX] = {0};

            res = read(itt_marker_file_fd, itt_lib_name, PATH_MAX - 1);
            if (res == -1)
            {
                ITT_ANDROID_LOGE("Unable to read %s file!", itt_marker_file_fd);
                res = close(itt_marker_file_fd);
                if (res == -1)
                {
                    ITT_ANDROID_LOGE("Unable to close %s file!", itt_marker_file_fd);
                }
                return lib_name;
            }
            ITT_ANDROID_LOGI("ITT Lib path: %s", itt_lib_name);
            res = close(itt_marker_file_fd);
            if (res == -1)
            {
                ITT_ANDROID_LOGE("Unable to close %s file!", itt_marker_file_fd);
                return lib_name;
            }
            ITT_ANDROID_LOGI("Set env %s to %s", ITT_TO_STR(LIB_VAR_NAME), itt_lib_name);
            res = setenv(ITT_TO_STR(LIB_VAR_NAME), itt_lib_name, 0);
            if (res == -1)
            {
                ITT_ANDROID_LOGE("Unable to set env var!");
                return lib_name;
            }
            lib_name = __itt_get_env_var(ITT_TO_STR(LIB_VAR_NAME));
            ITT_ANDROID_LOGI("ITT Lib path from env: %s", lib_name);
        }
    }
#endif

    return lib_name;
}