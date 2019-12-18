#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  vdec_type; } ;
struct TYPE_13__ {TYPE_1__ stat; scalar_t__ videotoolbox; } ;
struct TYPE_12__ {TYPE_2__* opaque; } ;
struct TYPE_11__ {int is_videotoolbox_open; } ;
typedef  int /*<<< orphan*/  IJKFF_Pipenode ;
typedef  TYPE_2__ IJKFF_Pipeline_Opaque ;
typedef  TYPE_3__ IJKFF_Pipeline ;
typedef  TYPE_4__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 int /*<<< orphan*/  FFP_MSG_VIDEO_DECODER_OPEN ; 
 int /*<<< orphan*/  FFP_PROPV_DECODER_AVCODEC ; 
 int /*<<< orphan*/  FFP_PROPV_DECODER_VIDEOTOOLBOX ; 
 int /*<<< orphan*/  ffp_notify_msg2 (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ffpipenode_create_video_decoder_from_ffplay (TYPE_4__*) ; 
 int /*<<< orphan*/ * ffpipenode_create_video_decoder_from_ios_videotoolbox (TYPE_4__*) ; 

__attribute__((used)) static IJKFF_Pipenode *func_open_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    IJKFF_Pipenode* node = NULL;
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    if (ffp->videotoolbox) {
        node = ffpipenode_create_video_decoder_from_ios_videotoolbox(ffp);
        if (!node)
            ALOGE("vtb fail!!! switch to ffmpeg decode!!!! \n");
    }
    if (node == NULL) {
        node = ffpipenode_create_video_decoder_from_ffplay(ffp);
        ffp->stat.vdec_type = FFP_PROPV_DECODER_AVCODEC;
        opaque->is_videotoolbox_open = false;
    } else {
        ffp->stat.vdec_type = FFP_PROPV_DECODER_VIDEOTOOLBOX;
        opaque->is_videotoolbox_open = true;
    }
    ffp_notify_msg2(ffp, FFP_MSG_VIDEO_DECODER_OPEN, opaque->is_videotoolbox_open);
    return node;
}