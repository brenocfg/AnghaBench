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
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/  jint ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * J4AC_java_nio_ByteBuffer__allocateDirect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 

jobject J4AC_java_nio_ByteBuffer__allocateDirect__catchAll(JNIEnv *env, jint capacity)
{
    jobject ret_object = J4AC_java_nio_ByteBuffer__allocateDirect(env, capacity);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        return NULL;
    }

    return ret_object;
}