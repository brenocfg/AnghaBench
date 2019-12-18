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
struct TYPE_2__ {size_t size; } ;
struct xz_dec {size_t in_start; int /*<<< orphan*/  crc; TYPE_1__ index; } ;
struct xz_buf {size_t in_pos; size_t in; } ;

/* Variables and functions */
 int /*<<< orphan*/  xz_crc32 (size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void index_update(struct xz_dec *s, const struct xz_buf *b)
{
	size_t in_used = b->in_pos - s->in_start;
	s->index.size += in_used;
	s->crc = xz_crc32(b->in + s->in_start, in_used, s->crc);
}