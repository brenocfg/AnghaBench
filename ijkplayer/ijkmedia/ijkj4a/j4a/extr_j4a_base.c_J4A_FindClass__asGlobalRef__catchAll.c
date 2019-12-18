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
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  J4A_FUNC_FAIL_TRACE1 (char const*) ; 
 int /*<<< orphan*/ * J4A_FindClass__catchAll (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * J4A_NewGlobalRef__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

jclass J4A_FindClass__asGlobalRef__catchAll(JNIEnv *env, const char *class_sign)
{
    jclass clazz_global = NULL;
    jclass clazz = J4A_FindClass__catchAll(env, class_sign);
    if (!clazz) {
        J4A_FUNC_FAIL_TRACE1(class_sign);
        goto fail;
    }

    clazz_global = J4A_NewGlobalRef__catchAll(env, clazz);
    if (!clazz_global) {
        J4A_FUNC_FAIL_TRACE1(class_sign);
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &clazz);
    return clazz_global;
}