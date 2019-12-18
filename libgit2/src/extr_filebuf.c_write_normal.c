#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  digest; scalar_t__ compute_digest; int /*<<< orphan*/  last_error; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  BUFERR_WRITE ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ p_write (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int write_normal(git_filebuf *file, void *source, size_t len)
{
	if (len > 0) {
		if (p_write(file->fd, (void *)source, len) < 0) {
			file->last_error = BUFERR_WRITE;
			return -1;
		}

		if (file->compute_digest)
			git_hash_update(&file->digest, source, len);
	}

	return 0;
}