#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ mediacodec_mpeg2; scalar_t__ mediacodec_hevc; scalar_t__ mediacodec_avc; scalar_t__ mediacodec_all_videos; } ;
struct TYPE_9__ {TYPE_1__* opaque; } ;
struct TYPE_8__ {int /*<<< orphan*/  weak_vout; } ;
typedef  int /*<<< orphan*/  IJKFF_Pipenode ;
typedef  TYPE_1__ IJKFF_Pipeline_Opaque ;
typedef  TYPE_2__ IJKFF_Pipeline ;
typedef  TYPE_3__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/ * ffpipenode_init_decoder_from_android_mediacodec (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static IJKFF_Pipenode *func_init_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    IJKFF_Pipenode        *node = NULL;

    if (ffp->mediacodec_all_videos || ffp->mediacodec_avc || ffp->mediacodec_hevc || ffp->mediacodec_mpeg2)
        node = ffpipenode_init_decoder_from_android_mediacodec(ffp, pipeline, opaque->weak_vout);

    return node;
}