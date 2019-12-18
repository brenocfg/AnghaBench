#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jmethodID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_5__ {int /*<<< orphan*/ * (* GetStaticMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/  J4A_FUNC_FAIL_TRACE2 (char const*,char const*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ; 

jmethodID J4A_GetStaticMethodID__catchAll(JNIEnv *env, jclass clazz, const char *method_name, const char *method_sign)
{
    jmethodID method_id = (*env)->GetStaticMethodID(env, clazz, method_name, method_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !method_id) {
        J4A_FUNC_FAIL_TRACE2(method_name, method_sign);
        method_id = NULL;
        goto fail;
    }

fail:
    return method_id;
}