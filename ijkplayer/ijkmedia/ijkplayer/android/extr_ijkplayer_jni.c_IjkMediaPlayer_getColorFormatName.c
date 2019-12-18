#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/  jint ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_4__ {int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 char* SDL_AMediaCodec_getColorFormatName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 

__attribute__((used)) static jstring
IjkMediaPlayer_getColorFormatName(JNIEnv *env, jclass clazz, jint mediaCodecColorFormat)
{
    const char *codec_name = SDL_AMediaCodec_getColorFormatName(mediaCodecColorFormat);
    if (!codec_name)
        return NULL ;

    return (*env)->NewStringUTF(env, codec_name);
}