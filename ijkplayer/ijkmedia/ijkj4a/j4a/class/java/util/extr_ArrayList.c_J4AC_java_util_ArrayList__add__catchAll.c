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
typedef  int /*<<< orphan*/  jobject ;
typedef  int jboolean ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int J4AC_java_util_ArrayList__add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 

jboolean J4AC_java_util_ArrayList__add__catchAll(JNIEnv *env, jobject thiz, jobject object)
{
    jboolean ret_value = J4AC_java_util_ArrayList__add(env, thiz, object);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return false;
    }

    return ret_value;
}