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
typedef  int /*<<< orphan*/ * jclass ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4A_ALOGE (char*) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J4A_FUNC_FAIL_TRACE () ; 
 int /*<<< orphan*/ * J4A_FindClass__catchAll (int /*<<< orphan*/ *,char const*) ; 
 int J4A_ThrowExceptionOfClass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

int J4A_ThrowException(JNIEnv* env, const char* class_sign, const char* msg)
{
    int ret = -1;

    if (J4A_ExceptionCheck__catchAll(env)) {
        J4A_ALOGE("pending exception throwed.\n");
    }

    jclass exceptionClass = J4A_FindClass__catchAll(env, class_sign);
    if (exceptionClass == NULL) {
        J4A_FUNC_FAIL_TRACE();
        ret = -1;
        goto fail;
    }

    ret = J4A_ThrowExceptionOfClass(env, exceptionClass, msg);
    if (ret) {
        J4A_FUNC_FAIL_TRACE();
        goto fail;
    }

    ret = 0;
fail:
    J4A_DeleteLocalRef__p(env, &exceptionClass);
    return ret;
}