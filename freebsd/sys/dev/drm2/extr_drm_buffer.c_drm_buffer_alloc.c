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
struct drm_buffer {int size; struct drm_buffer** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int,int,...) ; 
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int ENOMEM ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free (struct drm_buffer*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

int drm_buffer_alloc(struct drm_buffer **buf, int size)
{
	int nr_pages = size / PAGE_SIZE + 1;
	int idx;

	/* Allocating pointer table to end of structure makes drm_buffer
	 * variable sized */
	*buf = malloc(sizeof(struct drm_buffer) + nr_pages*sizeof(char *),
			DRM_MEM_DRIVER, M_ZERO | M_WAITOK);

	if (*buf == NULL) {
		DRM_ERROR("Failed to allocate drm buffer object to hold"
				" %d bytes in %d pages.\n",
				size, nr_pages);
		return -ENOMEM;
	}

	(*buf)->size = size;

	for (idx = 0; idx < nr_pages; ++idx) {

		(*buf)->data[idx] =
			malloc(min(PAGE_SIZE, size - idx * PAGE_SIZE),
				DRM_MEM_DRIVER, M_WAITOK);


		if ((*buf)->data[idx] == NULL) {
			DRM_ERROR("Failed to allocate %dth page for drm"
					" buffer with %d bytes and %d pages.\n",
					idx + 1, size, nr_pages);
			goto error_out;
		}

	}

	return 0;

error_out:

	/* Only last element can be null pointer so check for it first. */
	if ((*buf)->data[idx])
		free((*buf)->data[idx], DRM_MEM_DRIVER);

	for (--idx; idx >= 0; --idx)
		free((*buf)->data[idx], DRM_MEM_DRIVER);

	free(*buf, DRM_MEM_DRIVER);
	return -ENOMEM;
}