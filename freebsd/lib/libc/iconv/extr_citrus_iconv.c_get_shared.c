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
struct _citrus_iconv_shared {int ci_used_count; } ;
typedef  int /*<<< orphan*/  convname ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct _citrus_iconv_shared*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CITRUS_HASH_INSERT (int /*<<< orphan*/ *,struct _citrus_iconv_shared*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _CITRUS_HASH_SEARCH (int /*<<< orphan*/ *,struct _citrus_iconv_shared*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ci_hash_entry ; 
 int /*<<< orphan*/  ci_lock ; 
 int /*<<< orphan*/  ci_tailq_entry ; 
 int hash_func (char*) ; 
 int /*<<< orphan*/  match_func ; 
 int open_shared (struct _citrus_iconv_shared**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  shared_num_unused ; 
 int /*<<< orphan*/  shared_pool ; 
 int /*<<< orphan*/  shared_unused ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static int
get_shared(struct _citrus_iconv_shared * __restrict * __restrict rci,
    const char *src, const char *dst)
{
	struct _citrus_iconv_shared * ci;
	char convname[PATH_MAX];
	int hashval, ret = 0;

	snprintf(convname, sizeof(convname), "%s/%s", src, dst);

	WLOCK(&ci_lock);

	/* lookup alread existing entry */
	hashval = hash_func(convname);
	_CITRUS_HASH_SEARCH(&shared_pool, ci, ci_hash_entry, match_func,
	    convname, hashval);
	if (ci != NULL) {
		/* found */
		if (ci->ci_used_count == 0) {
			TAILQ_REMOVE(&shared_unused, ci, ci_tailq_entry);
			shared_num_unused--;
		}
		ci->ci_used_count++;
		*rci = ci;
		goto quit;
	}

	/* create new entry */
	ret = open_shared(&ci, convname, src, dst);
	if (ret)
		goto quit;

	_CITRUS_HASH_INSERT(&shared_pool, ci, ci_hash_entry, hashval);
	ci->ci_used_count = 1;
	*rci = ci;

quit:
	UNLOCK(&ci_lock);

	return (ret);
}