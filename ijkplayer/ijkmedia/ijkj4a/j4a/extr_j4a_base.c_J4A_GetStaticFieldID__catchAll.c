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
typedef  int /*<<< orphan*/ * jfieldID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_5__ {int /*<<< orphan*/ * (* GetStaticFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/  J4A_FUNC_FAIL_TRACE2 (char const*,char const*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ ,char const*,char const*) ; 

jfieldID J4A_GetStaticFieldID__catchAll(JNIEnv *env, jclass clazz, const char *field_name, const char *field_sign)
{
    jfieldID field_id = (*env)->GetStaticFieldID(env, clazz, field_name, field_sign);
    if (J4A_ExceptionCheck__catchAll(env) || !field_id) {
        J4A_FUNC_FAIL_TRACE2(field_name, field_sign);
        field_id = NULL;
        goto fail;
    }

fail:
    return field_id;
}