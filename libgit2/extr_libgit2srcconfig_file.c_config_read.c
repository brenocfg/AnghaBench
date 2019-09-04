#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_16__ {char* content; } ;
struct TYPE_12__ {TYPE_5__ ctx; TYPE_2__* file; } ;
typedef  TYPE_1__ git_config_parser ;
typedef  int /*<<< orphan*/  git_config_level_t ;
struct TYPE_13__ {int /*<<< orphan*/  path; int /*<<< orphan*/  checksum; } ;
typedef  TYPE_2__ git_config_file ;
typedef  int /*<<< orphan*/  git_config_entries ;
struct TYPE_14__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;
struct TYPE_15__ {int depth; int /*<<< orphan*/  level; int /*<<< orphan*/ * entries; int /*<<< orphan*/  file_path; int /*<<< orphan*/  const* repo; } ;
typedef  TYPE_4__ diskfile_parse_state ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int MAX_INCLUDE_DEPTH ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_config_parse (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_readbuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int git_hash_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_parse_ctx_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_on_variable ; 

__attribute__((used)) static int config_read(
	git_config_entries *entries,
	const git_repository *repo,
	git_config_file *file,
	git_config_level_t level,
	int depth)
{
	diskfile_parse_state parse_data;
	git_config_parser reader;
	git_buf contents = GIT_BUF_INIT;
	int error;

	if (depth >= MAX_INCLUDE_DEPTH) {
		git_error_set(GIT_ERROR_CONFIG, "maximum config include depth reached");
		return -1;
	}

	if ((error = git_futils_readbuffer(&contents, file->path)) < 0)
		goto out;

	git_parse_ctx_init(&reader.ctx, contents.ptr, contents.size);

	if ((error = git_hash_buf(&file->checksum, contents.ptr, contents.size)) < 0)
		goto out;

	/* Initialize the reading position */
	reader.file = file;
	git_parse_ctx_init(&reader.ctx, contents.ptr, contents.size);

	/* If the file is empty, there's nothing for us to do */
	if (!reader.ctx.content || *reader.ctx.content == '\0')
		goto out;

	parse_data.repo = repo;
	parse_data.file_path = file->path;
	parse_data.entries = entries;
	parse_data.level = level;
	parse_data.depth = depth;

	error = git_config_parse(&reader, NULL, read_on_variable, NULL, NULL, &parse_data);

out:
	git_buf_dispose(&contents);
	return error;
}