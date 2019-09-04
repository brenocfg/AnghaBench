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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_cb ; 
 int git_config_add_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_backend_free (int /*<<< orphan*/ *) ; 
 int git_config_backend_from_string (int /*<<< orphan*/ **,char const*,size_t) ; 
 int /*<<< orphan*/  git_config_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_new (int /*<<< orphan*/ **) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	git_config *cfg = NULL;
	git_config_backend *backend = NULL;
	int err = 0;

	if ((err = git_config_new(&cfg)) != 0) {
		goto out;
	}

	if ((err = git_config_backend_from_string(&backend, (const char*)data, size)) != 0) {
		goto out;
	}
	if ((err = git_config_add_backend(cfg, backend, 0, NULL, 0)) != 0) {
		goto out;
	}
	/* Now owned by the config */
	backend = NULL;

	git_config_foreach(cfg, foreach_cb, NULL);
 out:
	git_config_backend_free(backend);
	git_config_free(cfg);

	return 0;
}