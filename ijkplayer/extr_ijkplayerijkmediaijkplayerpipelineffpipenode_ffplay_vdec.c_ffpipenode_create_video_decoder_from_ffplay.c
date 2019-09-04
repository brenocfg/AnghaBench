#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vdec_type; } ;
struct TYPE_18__ {TYPE_3__ stat; TYPE_2__* is; } ;
struct TYPE_17__ {int /*<<< orphan*/  func_run_sync; int /*<<< orphan*/  func_destroy; TYPE_5__* opaque; } ;
struct TYPE_16__ {TYPE_7__* ffp; } ;
struct TYPE_15__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_12__ {TYPE_4__* avctx; } ;
struct TYPE_13__ {TYPE_1__ viddec; } ;
typedef  TYPE_5__ IJKFF_Pipenode_Opaque ;
typedef  TYPE_6__ IJKFF_Pipenode ;
typedef  TYPE_7__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AVCODEC_MODULE_NAME ; 
 int /*<<< orphan*/  FFP_PROPV_DECODER_AVCODEC ; 
 int /*<<< orphan*/  avcodec_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffp_set_video_codec_info (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ffpipenode_alloc (int) ; 
 int /*<<< orphan*/  func_destroy ; 
 int /*<<< orphan*/  func_run_sync ; 

IJKFF_Pipenode *ffpipenode_create_video_decoder_from_ffplay(FFPlayer *ffp)
{
    IJKFF_Pipenode *node = ffpipenode_alloc(sizeof(IJKFF_Pipenode_Opaque));
    if (!node)
        return node;

    IJKFF_Pipenode_Opaque *opaque = node->opaque;
    opaque->ffp         = ffp;

    node->func_destroy  = func_destroy;
    node->func_run_sync = func_run_sync;

    ffp_set_video_codec_info(ffp, AVCODEC_MODULE_NAME, avcodec_get_name(ffp->is->viddec.avctx->codec_id));
    ffp->stat.vdec_type = FFP_PROPV_DECODER_AVCODEC;
    return node;
}