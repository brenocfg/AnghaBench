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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 int /*<<< orphan*/  ALOGI (char*,int) ; 
 int J4AC_android_os_Build__VERSION__SDK_INT__get__catchAll (int /*<<< orphan*/ *) ; 
 scalar_t__ JNI_OK ; 
 int PROP_VALUE_MAX ; 
 scalar_t__ SDL_JNI_SetupThreadEnv (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  __system_property_get (char*,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int SDL_Android_GetApiLevel()
{
    static int SDK_INT = 0;
    if (SDK_INT > 0)
        return SDK_INT;

    JNIEnv *env = NULL;
    if (JNI_OK != SDL_JNI_SetupThreadEnv(&env)) {
        ALOGE("SDL_Android_GetApiLevel: SetupThreadEnv failed");
        return 0;
    }

    SDK_INT = J4AC_android_os_Build__VERSION__SDK_INT__get__catchAll(env);
    ALOGI("API-Level: %d\n", SDK_INT);
    return SDK_INT;
#if 0
    char value[PROP_VALUE_MAX];
    memset(value, 0, sizeof(value));
    __system_property_get("ro.build.version.sdk", value);
    SDK_INT = atoi(value);
    return SDK_INT;
#endif
}