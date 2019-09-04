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
struct TYPE_10__ {int /*<<< orphan*/  node_vdec; } ;
struct TYPE_9__ {TYPE_1__* opaque; } ;
struct TYPE_8__ {int /*<<< orphan*/  weak_vout; } ;
typedef  TYPE_1__ IJKFF_Pipeline_Opaque ;
typedef  TYPE_2__ IJKFF_Pipeline ;
typedef  TYPE_3__ FFPlayer ;

/* Variables and functions */
 int ffpipenode_config_from_android_mediacodec (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int func_config_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    int                       ret = NULL;

    if (ffp->node_vdec) {
        ret = ffpipenode_config_from_android_mediacodec(ffp, pipeline, opaque->weak_vout, ffp->node_vdec);
    }

    return ret;
}