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
struct v4l2_format {scalar_t__ type; int /*<<< orphan*/  fmt; } ;
struct l_v4l2_format {scalar_t__ type; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bsd_to_linux_v4l2_format(struct v4l2_format *vf, struct l_v4l2_format *lvf)
{
	lvf->type = vf->type;
	if (vf->type == V4L2_BUF_TYPE_VIDEO_OVERLAY
#ifdef V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY
	    || vf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY
#endif
	    )
		/*
		 * XXX TODO - needs 32 -> 64 bit conversion:
		 * (unused by webcams?)
		 */
		return (EINVAL);
	memcpy(&lvf->fmt, &vf->fmt, sizeof(vf->fmt));
	return (0);
}