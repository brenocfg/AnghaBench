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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
struct TYPE_4__ {int locked; int /*<<< orphan*/  locked_buf; TYPE_1__ file; int /*<<< orphan*/  locked_content; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_FILE_MODE ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_futils_readbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_lock(git_config_backend *_cfg)
{
	diskfile_backend *cfg = (diskfile_backend *) _cfg;
	int error;

	if ((error = git_filebuf_open(&cfg->locked_buf, cfg->file.path, 0, GIT_CONFIG_FILE_MODE)) < 0)
		return error;

	error = git_futils_readbuffer(&cfg->locked_content, cfg->file.path);
	if (error < 0 && error != GIT_ENOTFOUND) {
		git_filebuf_cleanup(&cfg->locked_buf);
		return error;
	}

	cfg->locked = true;
	return 0;

}