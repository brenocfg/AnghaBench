#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t length; } ;
struct TYPE_7__ {TYPE_2__ backends; } ;
typedef  TYPE_1__ git_config ;
typedef  int /*<<< orphan*/  backend_internal ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_DEC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backend_internal_free ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * git_vector_get (TYPE_2__*,size_t) ; 

__attribute__((used)) static void config_free(git_config *cfg)
{
	size_t i;
	backend_internal *internal;

	for (i = 0; i < cfg->backends.length; ++i) {
		internal = git_vector_get(&cfg->backends, i);
		GIT_REFCOUNT_DEC(internal, backend_internal_free);
	}

	git_vector_free(&cfg->backends);

	git__memzero(cfg, sizeof(*cfg));
	git__free(cfg);
}