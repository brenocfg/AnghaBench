#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; scalar_t__ pos; } ;
struct xz_dec {TYPE_1__ temp; int /*<<< orphan*/  index; int /*<<< orphan*/  block; scalar_t__ crc32; scalar_t__ pos; scalar_t__ allow_buf_error; int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_STREAM_HEADER ; 
 int /*<<< orphan*/  STREAM_HEADER_SIZE ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int) ; 

void xz_dec_reset(struct xz_dec *s)
{
	s->sequence = SEQ_STREAM_HEADER;
	s->allow_buf_error = 0;
	s->pos = 0;
	s->crc32 = 0;
	memzero(&s->block, sizeof(s->block));
	memzero(&s->index, sizeof(s->index));
	s->temp.pos = 0;
	s->temp.size = STREAM_HEADER_SIZE;
}