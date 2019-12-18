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
struct spu_context {int dummy; } ;
struct coredump_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct spu_context* coredump_next_context (int*) ; 
 int spu_acquire_saved (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release_saved (struct spu_context*) ; 
 int spufs_arch_write_note (struct spu_context*,int,struct coredump_params*,int) ; 
 TYPE_1__* spufs_coredump_read ; 

int spufs_coredump_extra_notes_write(struct coredump_params *cprm)
{
	struct spu_context *ctx;
	int fd, j, rc;

	fd = 0;
	while ((ctx = coredump_next_context(&fd)) != NULL) {
		rc = spu_acquire_saved(ctx);
		if (rc)
			return rc;

		for (j = 0; spufs_coredump_read[j].name != NULL; j++) {
			rc = spufs_arch_write_note(ctx, j, cprm, fd);
			if (rc) {
				spu_release_saved(ctx);
				return rc;
			}
		}

		spu_release_saved(ctx);

		/* start searching the next fd next time */
		fd++;
	}

	return 0;
}