#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  backends; } ;
typedef  TYPE_1__ git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  config_backend_cmp ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 TYPE_1__* git__malloc (int) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

int git_config_new(git_config **out)
{
	git_config *cfg;

	cfg = git__malloc(sizeof(git_config));
	GIT_ERROR_CHECK_ALLOC(cfg);

	memset(cfg, 0x0, sizeof(git_config));

	if (git_vector_init(&cfg->backends, 3, config_backend_cmp) < 0) {
		git__free(cfg);
		return -1;
	}

	*out = cfg;
	GIT_REFCOUNT_INC(cfg);
	return 0;
}