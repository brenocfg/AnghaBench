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
struct TYPE_7__ {unsigned long userptr; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct v4l2_buffer {scalar_t__ memory; int /*<<< orphan*/  reserved; int /*<<< orphan*/  input; int /*<<< orphan*/  length; TYPE_3__ m; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; TYPE_1__ timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  userptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct l_v4l2_buffer {scalar_t__ memory; int /*<<< orphan*/  reserved; int /*<<< orphan*/  input; int /*<<< orphan*/  length; TYPE_4__ m; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; TYPE_2__ timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ PTRIN (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
linux_to_bsd_v4l2_buffer(struct l_v4l2_buffer *lvb, struct v4l2_buffer *vb)
{
	vb->index = lvb->index;
	vb->type = lvb->type;
	vb->bytesused = lvb->bytesused;
	vb->flags = lvb->flags;
	vb->field = lvb->field;
	vb->timestamp.tv_sec = lvb->timestamp.tv_sec;
	vb->timestamp.tv_usec = lvb->timestamp.tv_usec;
	memcpy(&vb->timecode, &lvb->timecode, sizeof (lvb->timecode));
	vb->sequence = lvb->sequence;
	vb->memory = lvb->memory;
	if (lvb->memory == V4L2_MEMORY_USERPTR)
		/* possible pointer size conversion */
		vb->m.userptr = (unsigned long)PTRIN(lvb->m.userptr);
	else
		vb->m.offset = lvb->m.offset;
	vb->length = lvb->length;
	vb->input = lvb->input;
	vb->reserved = lvb->reserved;
	return (0);
}