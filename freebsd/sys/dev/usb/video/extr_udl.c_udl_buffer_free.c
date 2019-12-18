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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct udl_buffer {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct udl_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udl_buffer_head ; 
 int /*<<< orphan*/  udl_buffer_mtx ; 

__attribute__((used)) static void
udl_buffer_free(void *_buf, uint32_t size)
{
	struct udl_buffer *buf;

	/* check for NULL pointer */
	if (_buf == NULL)
		return;
	/* compute pointer to recycle list */
	buf = (struct udl_buffer *)(((uint8_t *)_buf) + size);

	/*
	 * Memory mapped buffers should never be freed.
	 * Put display buffer into a recycle list.
	 */
	mtx_lock(&udl_buffer_mtx);
	buf->size = size;
	TAILQ_INSERT_TAIL(&udl_buffer_head, buf, entry);
	mtx_unlock(&udl_buffer_mtx);
}