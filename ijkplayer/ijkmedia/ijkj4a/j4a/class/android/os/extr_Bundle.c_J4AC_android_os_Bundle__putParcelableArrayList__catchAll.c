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
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4AC_android_os_Bundle__putParcelableArrayList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 

void J4AC_android_os_Bundle__putParcelableArrayList__catchAll(JNIEnv *env, jobject thiz, jstring key, jobject value)
{
    J4AC_android_os_Bundle__putParcelableArrayList(env, thiz, key, value);
    J4A_ExceptionCheck__catchAll(env);
}