#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {size_t max_delta_cache_size; size_t cache_max_small_delta_size; size_t big_file_threshold; size_t window_memory_limit; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 size_t GIT_PACK_BIG_FILE_THRESHOLD ; 
 size_t GIT_PACK_DELTA_CACHE_LIMIT ; 
 size_t GIT_PACK_DELTA_CACHE_SIZE ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_int64 (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int packbuilder_config(git_packbuilder *pb)
{
	git_config *config;
	int ret = 0;
	int64_t val;

	if ((ret = git_repository_config_snapshot(&config, pb->repo)) < 0)
		return ret;

#define config_get(KEY,DST,DFLT) do { \
	ret = git_config_get_int64(&val, config, KEY); \
	if (!ret) { \
		if (!git__is_sizet(val)) { \
			git_error_set(GIT_ERROR_CONFIG, \
				"configuration value '%s' is too large", KEY); \
			ret = -1; \
			goto out; \
		} \
		(DST) = (size_t)val; \
	} else if (ret == GIT_ENOTFOUND) { \
	    (DST) = (DFLT); \
	    ret = 0; \
	} else if (ret < 0) goto out; } while (0)

	config_get("pack.deltaCacheSize", pb->max_delta_cache_size,
		   GIT_PACK_DELTA_CACHE_SIZE);
	config_get("pack.deltaCacheLimit", pb->cache_max_small_delta_size,
		   GIT_PACK_DELTA_CACHE_LIMIT);
	config_get("pack.deltaCacheSize", pb->big_file_threshold,
		   GIT_PACK_BIG_FILE_THRESHOLD);
	config_get("pack.windowMemory", pb->window_memory_limit, 0);

#undef config_get

out:
	git_config_free(config);

	return ret;
}