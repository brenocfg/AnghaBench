#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct TYPE_3__ {int locked; TYPE_2__ locked_content; int /*<<< orphan*/  locked_buf; } ;
typedef  TYPE_1__ diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_unlock(git_config_backend *_cfg, int success)
{
	diskfile_backend *cfg = (diskfile_backend *) _cfg;
	int error = 0;

	if (success) {
		git_filebuf_write(&cfg->locked_buf, cfg->locked_content.ptr, cfg->locked_content.size);
		error = git_filebuf_commit(&cfg->locked_buf);
	}

	git_filebuf_cleanup(&cfg->locked_buf);
	git_buf_dispose(&cfg->locked_content);
	cfg->locked = false;

	return error;
}