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
struct video_code {int /*<<< orphan*/  data; int /*<<< orphan*/  datasize; int /*<<< orphan*/  loadwhat; } ;
struct l_video_code {int /*<<< orphan*/  data; int /*<<< orphan*/  datasize; int /*<<< orphan*/  loadwhat; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_VIDEO_CODE_LOADWHAT_SIZE ; 
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_to_bsd_v4l_code(struct l_video_code *lvc, struct video_code *vc)
{
	strlcpy(vc->loadwhat, lvc->loadwhat, LINUX_VIDEO_CODE_LOADWHAT_SIZE);
	vc->datasize = lvc->datasize;
	vc->data = PTRIN(lvc->data);	/* possible pointer size conversion */
	return (0);
}