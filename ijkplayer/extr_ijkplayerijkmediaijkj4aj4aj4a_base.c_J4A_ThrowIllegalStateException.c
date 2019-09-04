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
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int J4A_ThrowException (int /*<<< orphan*/ *,char*,char const*) ; 

int J4A_ThrowIllegalStateException(JNIEnv *env, const char* msg)
{
    return J4A_ThrowException(env, "java/lang/IllegalStateException", msg);
}