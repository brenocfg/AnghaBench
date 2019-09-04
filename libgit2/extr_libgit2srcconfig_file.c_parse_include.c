#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct config_file {void* path; int /*<<< orphan*/  includes; } ;
struct TYPE_7__ {TYPE_1__* file; } ;
typedef  TYPE_2__ git_config_parser ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_8__ {scalar_t__ depth; int /*<<< orphan*/  level; int /*<<< orphan*/  repo; int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ diskfile_parse_state ;
struct TYPE_6__ {int /*<<< orphan*/  includes; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct config_file*) ; 
 int config_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct config_file*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 struct config_file* git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_array_init (int /*<<< orphan*/ ) ; 
 void* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_path_dirname_r (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int included_path (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  memset (struct config_file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_include(git_config_parser *reader,
	diskfile_parse_state *parse_data, const char *file)
{
	struct config_file *include;
	git_buf path = GIT_BUF_INIT;
	char *dir;
	int result;

	if (!file)
		return 0;

	if ((result = git_path_dirname_r(&path, reader->file->path)) < 0)
		return result;

	dir = git_buf_detach(&path);
	result = included_path(&path, dir, file);
	git__free(dir);

	if (result < 0)
		return result;

	include = git_array_alloc(reader->file->includes);
	GIT_ERROR_CHECK_ALLOC(include);
	memset(include, 0, sizeof(*include));
	git_array_init(include->includes);
	include->path = git_buf_detach(&path);

	result = config_read(parse_data->entries, parse_data->repo,
		include, parse_data->level, parse_data->depth+1);

	if (result == GIT_ENOTFOUND) {
		git_error_clear();
		result = 0;
	}

	return result;
}