#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_parser ;
typedef  int /*<<< orphan*/  git_config_level_t ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_6__ {int /*<<< orphan*/  level; int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ config_memory_parse_data ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  entries; TYPE_1__ cfg; } ;
typedef  TYPE_3__ config_memory_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_PARSE_CTX_INIT ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int git_config_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_parser_dispose (int /*<<< orphan*/ *) ; 
 int git_config_parser_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_variable_cb ; 

__attribute__((used)) static int config_memory_open(git_config_backend *backend, git_config_level_t level, const git_repository *repo)
{
	config_memory_backend *memory_backend = (config_memory_backend *) backend;
	git_config_parser parser = GIT_PARSE_CTX_INIT;
	config_memory_parse_data parse_data;
	int error;

	GIT_UNUSED(repo);

	if ((error = git_config_parser_init(&parser, "in-memory", memory_backend->cfg.ptr,
					    memory_backend->cfg.size)) < 0)
		goto out;
	parse_data.entries = memory_backend->entries;
	parse_data.level = level;

	if ((error = git_config_parse(&parser, NULL, read_variable_cb, NULL, NULL, &parse_data)) < 0)
		goto out;

out:
	git_config_parser_dispose(&parser);
	return error;
}