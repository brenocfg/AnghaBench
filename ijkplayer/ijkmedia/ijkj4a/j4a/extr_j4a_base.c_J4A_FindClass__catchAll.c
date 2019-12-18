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
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_5__ {int /*<<< orphan*/ * (* FindClass ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/  J4A_FUNC_FAIL_TRACE () ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 

jclass J4A_FindClass__catchAll(JNIEnv *env, const char *class_sign)
{
    jclass clazz = (*env)->FindClass(env, class_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !(clazz)) {
        J4A_FUNC_FAIL_TRACE();
        clazz = NULL;
        goto fail;
    }

fail:
    return clazz;
}