#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jboolean ;
struct TYPE_6__ {int /*<<< orphan*/  method_add; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* CallBooleanMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 TYPE_3__ class_J4AC_java_util_ArrayList ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jboolean J4AC_java_util_ArrayList__add(JNIEnv *env, jobject thiz, jobject object)
{
    return (*env)->CallBooleanMethod(env, thiz, class_J4AC_java_util_ArrayList.method_add, object);
}