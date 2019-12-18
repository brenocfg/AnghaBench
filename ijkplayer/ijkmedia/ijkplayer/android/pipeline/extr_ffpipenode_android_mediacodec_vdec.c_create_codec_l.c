#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  codec_name; int /*<<< orphan*/  mime_type; } ;
typedef  TYPE_2__ ijkmp_mediacodecinfo_context ;
struct TYPE_9__ {TYPE_3__* opaque; } ;
struct TYPE_8__ {int quirk_reconfigure_with_new_codec; int n_buf_out; int frame_rotate_degrees; TYPE_1__* codecpar; int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; scalar_t__* acodec_name; int /*<<< orphan*/ * jsurface; TYPE_2__ mcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  SDL_AMediaCodec ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  TYPE_3__ IJKFF_Pipenode_Opaque ;
typedef  TYPE_4__ IJKFF_Pipenode ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGD (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_AMediaCodecDummy_create () ; 
 int /*<<< orphan*/ * SDL_AMediaCodecJava_createByCodecName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_AMediaCodecJava_createDecoderByType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static SDL_AMediaCodec *create_codec_l(JNIEnv *env, IJKFF_Pipenode *node)
{
    IJKFF_Pipenode_Opaque        *opaque   = node->opaque;
    ijkmp_mediacodecinfo_context *mcc      = &opaque->mcc;
    SDL_AMediaCodec              *acodec   = NULL;

    if (opaque->jsurface == NULL) {
        // we don't need real codec if we don't have a surface
        acodec = SDL_AMediaCodecDummy_create();
    } else {
        acodec = SDL_AMediaCodecJava_createByCodecName(env, mcc->codec_name);
        if (acodec) {
            strncpy(opaque->acodec_name, mcc->codec_name, sizeof(opaque->acodec_name) / sizeof(*opaque->acodec_name));
            opaque->acodec_name[sizeof(opaque->acodec_name) / sizeof(*opaque->acodec_name) - 1] = 0;
        }
    }

#if 0
    if (!acodec)
        acodec = SDL_AMediaCodecJava_createDecoderByType(env, mcc->mime_type);
#endif

    if (acodec) {
        // QUIRK: always recreate MediaCodec for reconfigure
        opaque->quirk_reconfigure_with_new_codec = true;
        /*-
        if (0 == strncasecmp(mcc->codec_name, "OMX.TI.DUCATI1.", 15)) {
            opaque->quirk_reconfigure_with_new_codec = true;
        }
        */
        /* delaying output makes it possible to correct frame order, hopefully */
        if (0 == strncasecmp(mcc->codec_name, "OMX.TI.DUCATI1.", 15)) {
            /* this is the only acceptable value on Nexus S */
            opaque->n_buf_out = 1;
            ALOGD("using buffered output for %s", mcc->codec_name);
        }
    }

    if (opaque->frame_rotate_degrees == 90 || opaque->frame_rotate_degrees == 270) {
        opaque->frame_width  = opaque->codecpar->height;
        opaque->frame_height = opaque->codecpar->width;
    } else {
        opaque->frame_width  = opaque->codecpar->width;
        opaque->frame_height = opaque->codecpar->height;
    }

    return acodec;
}