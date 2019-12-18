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
struct pattern_list {int nr; struct path_pattern** patterns; } ;
struct path_pattern {char* pattern; int nowildcardlen; int flags; int baselen; char* base; int /*<<< orphan*/  patternlen; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int DT_DIR ; 
 int DT_UNKNOWN ; 
 int PATTERN_FLAG_MUSTBEDIR ; 
 int PATTERN_FLAG_NODIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_dtype (int /*<<< orphan*/ *,struct index_state*,char const*,int) ; 
 scalar_t__ match_basename (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ match_pathname (char const*,int,char*,int,char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct path_pattern *last_matching_pattern_from_list(const char *pathname,
						       int pathlen,
						       const char *basename,
						       int *dtype,
						       struct pattern_list *pl,
						       struct index_state *istate)
{
	struct path_pattern *res = NULL; /* undecided */
	int i;

	if (!pl->nr)
		return NULL;	/* undefined */

	for (i = pl->nr - 1; 0 <= i; i--) {
		struct path_pattern *pattern = pl->patterns[i];
		const char *exclude = pattern->pattern;
		int prefix = pattern->nowildcardlen;

		if (pattern->flags & PATTERN_FLAG_MUSTBEDIR) {
			if (*dtype == DT_UNKNOWN)
				*dtype = get_dtype(NULL, istate, pathname, pathlen);
			if (*dtype != DT_DIR)
				continue;
		}

		if (pattern->flags & PATTERN_FLAG_NODIR) {
			if (match_basename(basename,
					   pathlen - (basename - pathname),
					   exclude, prefix, pattern->patternlen,
					   pattern->flags)) {
				res = pattern;
				break;
			}
			continue;
		}

		assert(pattern->baselen == 0 ||
		       pattern->base[pattern->baselen - 1] == '/');
		if (match_pathname(pathname, pathlen,
				   pattern->base,
				   pattern->baselen ? pattern->baselen - 1 : 0,
				   exclude, prefix, pattern->patternlen,
				   pattern->flags)) {
			res = pattern;
			break;
		}
	}
	return res;
}