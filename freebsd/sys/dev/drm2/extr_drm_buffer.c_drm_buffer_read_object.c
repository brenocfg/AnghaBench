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
struct drm_buffer {int /*<<< orphan*/ ** data; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  drm_buffer_advance (struct drm_buffer*,int) ; 
 int drm_buffer_index (struct drm_buffer*) ; 
 int drm_buffer_page (struct drm_buffer*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

void *drm_buffer_read_object(struct drm_buffer *buf,
		int objsize, void *stack_obj)
{
	int idx = drm_buffer_index(buf);
	int page = drm_buffer_page(buf);
	void *obj = NULL;

	if (idx + objsize <= PAGE_SIZE) {
		obj = &buf->data[page][idx];
	} else {
		/* The object is split which forces copy to temporary object.*/
		int beginsz = PAGE_SIZE - idx;
		memcpy(stack_obj, &buf->data[page][idx], beginsz);

		memcpy((char *)stack_obj + beginsz, &buf->data[page + 1][0],
				objsize - beginsz);

		obj = stack_obj;
	}

	drm_buffer_advance(buf, objsize);
	return obj;
}