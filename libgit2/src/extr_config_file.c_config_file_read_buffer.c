#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_11__ {char* content; } ;
struct TYPE_8__ {TYPE_4__ ctx; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_config_parser ;
typedef  int /*<<< orphan*/  git_config_level_t ;
typedef  int /*<<< orphan*/  git_config_entries ;
struct TYPE_9__ {int depth; int /*<<< orphan*/  level; int /*<<< orphan*/ * entries; TYPE_3__* file; int /*<<< orphan*/  const* repo; } ;
typedef  TYPE_2__ config_file_parse_data ;
struct TYPE_10__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ config_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int MAX_INCLUDE_DEPTH ; 
 int git_config_parse (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_parse_ctx_init (TYPE_4__*,char const*,size_t) ; 
 int /*<<< orphan*/  read_on_variable ; 

__attribute__((used)) static int config_file_read_buffer(
	git_config_entries *entries,
	const git_repository *repo,
	config_file *file,
	git_config_level_t level,
	int depth,
	const char *buf,
	size_t buflen)
{
	config_file_parse_data parse_data;
	git_config_parser reader;
	int error;

	if (depth >= MAX_INCLUDE_DEPTH) {
		git_error_set(GIT_ERROR_CONFIG, "maximum config include depth reached");
		return -1;
	}

	/* Initialize the reading position */
	reader.path = file->path;
	git_parse_ctx_init(&reader.ctx, buf, buflen);

	/* If the file is empty, there's nothing for us to do */
	if (!reader.ctx.content || *reader.ctx.content == '\0') {
		error = 0;
		goto out;
	}

	parse_data.repo = repo;
	parse_data.file = file;
	parse_data.entries = entries;
	parse_data.level = level;
	parse_data.depth = depth;

	error = git_config_parse(&reader, NULL, read_on_variable, NULL, NULL, &parse_data);

out:
	return error;
}