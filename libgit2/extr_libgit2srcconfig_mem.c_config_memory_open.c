#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/ * file; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ git_config_parser ;
typedef  int /*<<< orphan*/  git_config_level_t ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_9__ {int /*<<< orphan*/  level; int /*<<< orphan*/  entries; } ;
typedef  TYPE_3__ config_memory_parse_data ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/  entries; TYPE_1__ cfg; } ;
typedef  TYPE_4__ config_memory_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int git_config_parse (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_parse_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  read_variable_cb ; 

__attribute__((used)) static int config_memory_open(git_config_backend *backend, git_config_level_t level, const git_repository *repo)
{
	config_memory_backend *memory_backend = (config_memory_backend *) backend;
	config_memory_parse_data parse_data;
	git_config_parser reader;

	GIT_UNUSED(repo);

	if (memory_backend->cfg.size == 0)
		return 0;

	git_parse_ctx_init(&reader.ctx, memory_backend->cfg.ptr, memory_backend->cfg.size);
	reader.file = NULL;
	parse_data.entries = memory_backend->entries;
	parse_data.level = level;

	return git_config_parse(&reader, NULL, read_variable_cb, NULL, NULL, &parse_data);
}