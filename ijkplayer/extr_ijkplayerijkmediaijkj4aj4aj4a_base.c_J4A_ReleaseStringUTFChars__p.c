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
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4A_ReleaseStringUTFChars (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

void J4A_ReleaseStringUTFChars__p(JNIEnv *env, jstring str, const char **c_str)
{
    if (!str || !c_str)
        return;
    J4A_ReleaseStringUTFChars(env, str, *c_str);
    *c_str = NULL;
}