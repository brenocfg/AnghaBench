#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * jstring ;
typedef  scalar_t__ jsize ;
typedef  int /*<<< orphan*/  jclass ;
typedef  int /*<<< orphan*/  jbyteArray ;
typedef  int /*<<< orphan*/  jbyte ;
struct TYPE_7__ {scalar_t__ (* GetArrayLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseByteArrayElements ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char*) ;int /*<<< orphan*/ * (* GetByteArrayElements ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int AV_BASE64_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  JNI_ABORT ; 
 int /*<<< orphan*/  av_base64_encode (char*,int,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 scalar_t__ stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jstring
FFmpegApi_av_base64_encode(JNIEnv *env, jclass clazz, jbyteArray in)
{
    jstring ret_string = NULL;
    char*   out_buffer = 0;
    int     out_size   = 0;
    jbyte*  in_buffer  = 0;
    jsize   in_size    = (*env)->GetArrayLength(env, in);
    if (in_size <= 0)
        goto fail;

    in_buffer = (*env)->GetByteArrayElements(env, in, NULL);
    if (!in_buffer)
        goto fail;

    out_size = AV_BASE64_SIZE(in_size);
    out_buffer = malloc(out_size + 1);
    if (!out_buffer)
        goto fail;
    out_buffer[out_size] = 0;

    if (!av_base64_encode(out_buffer, out_size, (const uint8_t *)in_buffer, in_size))
        goto fail;

    ret_string = (*env)->NewStringUTF(env, out_buffer);
fail:
    if (in_buffer) {
        (*env)->ReleaseByteArrayElements(env, in, in_buffer, JNI_ABORT);
        in_buffer = NULL;
    }
    if (out_buffer) {
        free(out_buffer);
        out_buffer = NULL;
    }
    return ret_string;
}