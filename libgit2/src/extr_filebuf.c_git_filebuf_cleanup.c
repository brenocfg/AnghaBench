#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; scalar_t__ path_lock; scalar_t__ path_original; int /*<<< orphan*/  zs; scalar_t__ z_buf; scalar_t__ buffer; scalar_t__ compute_digest; int /*<<< orphan*/  digest; int /*<<< orphan*/  did_rename; scalar_t__ created_lock; scalar_t__ fd_is_open; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (scalar_t__) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ git_path_exists (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_unlink (scalar_t__) ; 

void git_filebuf_cleanup(git_filebuf *file)
{
	if (file->fd_is_open && file->fd >= 0)
		p_close(file->fd);

	if (file->created_lock && !file->did_rename && file->path_lock && git_path_exists(file->path_lock))
		p_unlink(file->path_lock);

	if (file->compute_digest) {
		git_hash_ctx_cleanup(&file->digest);
		file->compute_digest = 0;
	}

	if (file->buffer)
		git__free(file->buffer);

	/* use the presence of z_buf to decide if we need to deflateEnd */
	if (file->z_buf) {
		git__free(file->z_buf);
		deflateEnd(&file->zs);
	}

	if (file->path_original)
		git__free(file->path_original);
	if (file->path_lock)
		git__free(file->path_lock);

	memset(file, 0x0, sizeof(git_filebuf));
	file->fd = -1;
}