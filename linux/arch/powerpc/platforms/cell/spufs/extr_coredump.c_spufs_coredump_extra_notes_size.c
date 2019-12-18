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
struct spu_context {int dummy; } ;

/* Variables and functions */
 struct spu_context* coredump_next_context (int*) ; 
 int spu_acquire_saved (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release_saved (struct spu_context*) ; 
 int spufs_ctx_note_size (struct spu_context*,int) ; 

int spufs_coredump_extra_notes_size(void)
{
	struct spu_context *ctx;
	int size = 0, rc, fd;

	fd = 0;
	while ((ctx = coredump_next_context(&fd)) != NULL) {
		rc = spu_acquire_saved(ctx);
		if (rc)
			break;
		rc = spufs_ctx_note_size(ctx, fd);
		spu_release_saved(ctx);
		if (rc < 0)
			break;

		size += rc;

		/* start searching the next fd next time */
		fd++;
	}

	return size;
}