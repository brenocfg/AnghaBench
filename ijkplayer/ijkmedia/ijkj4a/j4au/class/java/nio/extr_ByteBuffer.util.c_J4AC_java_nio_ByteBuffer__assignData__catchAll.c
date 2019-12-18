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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * J4AC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J4AC_java_nio_ByteBuffer__limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 

int J4AC_java_nio_ByteBuffer__assignData__catchAll(JNIEnv *env, jobject thiz, void* data, size_t size)
{
    jobject buffer = J4AC_java_nio_ByteBuffer__limit(env, thiz, size);
    if (J4A_ExceptionCheck__catchAll(env) || !buffer)
        return -1;
    J4A_DeleteLocalRef__p(env, &buffer);

    uint8_t *c_buffer = J4AC_java_nio_ByteBuffer__getDirectBufferAddress__catchAll(env, thiz);
    if (!c_buffer)
        return -1;

    memcpy(c_buffer, data, size);
    return 0;
}