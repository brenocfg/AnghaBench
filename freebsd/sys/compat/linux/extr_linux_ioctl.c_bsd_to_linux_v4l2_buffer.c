#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  userptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct v4l2_buffer {scalar_t__ memory; int /*<<< orphan*/  reserved; int /*<<< orphan*/  input; int /*<<< orphan*/  length; TYPE_4__ m; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; TYPE_2__ timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  userptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct l_v4l2_buffer {scalar_t__ memory; int /*<<< orphan*/  reserved; int /*<<< orphan*/  input; int /*<<< orphan*/  length; TYPE_3__ m; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; TYPE_1__ timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bsd_to_linux_v4l2_buffer(struct v4l2_buffer *vb, struct l_v4l2_buffer *lvb)
{
	lvb->index = vb->index;
	lvb->type = vb->type;
	lvb->bytesused = vb->bytesused;
	lvb->flags = vb->flags;
	lvb->field = vb->field;
	lvb->timestamp.tv_sec = vb->timestamp.tv_sec;
	lvb->timestamp.tv_usec = vb->timestamp.tv_usec;
	memcpy(&lvb->timecode, &vb->timecode, sizeof (vb->timecode));
	lvb->sequence = vb->sequence;
	lvb->memory = vb->memory;
	if (vb->memory == V4L2_MEMORY_USERPTR)
		/* possible pointer size conversion */
		lvb->m.userptr = PTROUT(vb->m.userptr);
	else
		lvb->m.offset = vb->m.offset;
	lvb->length = vb->length;
	lvb->input = vb->input;
	lvb->reserved = vb->reserved;
	return (0);
}