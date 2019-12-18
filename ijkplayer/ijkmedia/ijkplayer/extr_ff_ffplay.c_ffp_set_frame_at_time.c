#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int num; int count; int width; int height; scalar_t__ end_time; scalar_t__ start_time; int /*<<< orphan*/  img_path; } ;
struct TYPE_5__ {TYPE_4__* get_img_info; } ;
typedef  int /*<<< orphan*/  GetImgInfo ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_MSG_GET_IMG_STATE ; 
 int HD_IMAGE ; 
 int SD_IMAGE ; 
 TYPE_4__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 int /*<<< orphan*/  ffp_notify_msg3 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ffp_set_frame_at_time(FFPlayer *ffp, const char *path, int64_t start_time, int64_t end_time, int num, int definition) {
    if (!ffp->get_img_info) {
        ffp->get_img_info = av_mallocz(sizeof(GetImgInfo));
        if (!ffp->get_img_info) {
            ffp_notify_msg3(ffp, FFP_MSG_GET_IMG_STATE, 0, -1);
            return;
        }
    }

    if (start_time >= 0 && num > 0 && end_time >= 0 && end_time >= start_time) {
        ffp->get_img_info->img_path   = av_strdup(path);
        ffp->get_img_info->start_time = start_time;
        ffp->get_img_info->end_time   = end_time;
        ffp->get_img_info->num        = num;
        ffp->get_img_info->count      = num;
        if (definition== HD_IMAGE) {
            ffp->get_img_info->width  = 640;
            ffp->get_img_info->height = 360;
        } else if (definition == SD_IMAGE) {
            ffp->get_img_info->width  = 320;
            ffp->get_img_info->height = 180;
        } else {
            ffp->get_img_info->width  = 160;
            ffp->get_img_info->height = 90;
        }
    } else {
        ffp->get_img_info->count = 0;
        ffp_notify_msg3(ffp, FFP_MSG_GET_IMG_STATE, 0, -1);
    }
}