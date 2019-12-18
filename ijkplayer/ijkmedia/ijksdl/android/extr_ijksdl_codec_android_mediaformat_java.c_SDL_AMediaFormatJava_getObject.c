#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_5__ {scalar_t__ opaque; } ;
struct TYPE_4__ {int /*<<< orphan*/ * android_media_format; } ;
typedef  TYPE_1__ SDL_AMediaFormat_Opaque ;
typedef  TYPE_2__ SDL_AMediaFormat ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */

jobject SDL_AMediaFormatJava_getObject(JNIEnv *env, const SDL_AMediaFormat *thiz)
{
    if (!thiz || !thiz->opaque)
        return NULL;

    SDL_AMediaFormat_Opaque *opaque = (SDL_AMediaFormat_Opaque *)thiz->opaque;
    return opaque->android_media_format;
}