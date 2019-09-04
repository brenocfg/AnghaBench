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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  git_config_backend ;
typedef  int /*<<< orphan*/  diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int config_refresh (int /*<<< orphan*/ *) ; 
 int config_write (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_config__normalize_name (char const*,char**) ; 
 int /*<<< orphan*/  git_error_set_regex (int /*<<< orphan*/ *,int) ; 
 int p_regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_set_multivar(
	git_config_backend *cfg, const char *name, const char *regexp, const char *value)
{
	diskfile_backend *b = (diskfile_backend *)cfg;
	char *key;
	regex_t preg;
	int result;

	assert(regexp);

	if ((result = git_config__normalize_name(name, &key)) < 0)
		return result;

	result = p_regcomp(&preg, regexp, REG_EXTENDED);
	if (result != 0) {
		git_error_set_regex(&preg, result);
		result = -1;
		goto out;
	}

	/* If we do have it, set call config_write() and reload */
	if ((result = config_write(b, name, key, &preg, value)) < 0)
		goto out;

	result = config_refresh(cfg);

out:
	git__free(key);
	regfree(&preg);

	return result;
}