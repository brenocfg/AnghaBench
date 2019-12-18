#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct repository_format {int /*<<< orphan*/  hash_algo; } ;
struct repository {int /*<<< orphan*/  commondir; int /*<<< orphan*/  parsed_objects; int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 struct repository_format REPOSITORY_FORMAT_INIT ; 
 int /*<<< orphan*/  clear_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  memset (struct repository*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parsed_object_pool_new () ; 
 int /*<<< orphan*/  raw_object_store_new () ; 
 scalar_t__ read_and_verify_repository_format (struct repository_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 scalar_t__ repo_init_gitdir (struct repository*,char const*) ; 
 int /*<<< orphan*/  repo_set_hash_algo (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_set_worktree (struct repository*,char const*) ; 

int repo_init(struct repository *repo,
	      const char *gitdir,
	      const char *worktree)
{
	struct repository_format format = REPOSITORY_FORMAT_INIT;
	memset(repo, 0, sizeof(*repo));

	repo->objects = raw_object_store_new();
	repo->parsed_objects = parsed_object_pool_new();

	if (repo_init_gitdir(repo, gitdir))
		goto error;

	if (read_and_verify_repository_format(&format, repo->commondir))
		goto error;

	repo_set_hash_algo(repo, format.hash_algo);

	if (worktree)
		repo_set_worktree(repo, worktree);

	clear_repository_format(&format);
	return 0;

error:
	repo_clear(repo);
	return -1;
}