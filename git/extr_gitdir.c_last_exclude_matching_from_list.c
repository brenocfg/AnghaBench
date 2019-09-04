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
struct index_state {int dummy; } ;
struct exclude_list {int nr; struct exclude** excludes; } ;
struct exclude {char* pattern; int nowildcardlen; int flags; int baselen; char* base; int /*<<< orphan*/  patternlen; } ;

/* Variables and functions */
 int DT_DIR ; 
 int DT_UNKNOWN ; 
 int EXC_FLAG_MUSTBEDIR ; 
 int EXC_FLAG_NODIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_dtype (int /*<<< orphan*/ *,struct index_state*,char const*,int) ; 
 scalar_t__ match_basename (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ match_pathname (char const*,int,char*,int,char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct exclude *last_exclude_matching_from_list(const char *pathname,
						       int pathlen,
						       const char *basename,
						       int *dtype,
						       struct exclude_list *el,
						       struct index_state *istate)
{
	struct exclude *exc = NULL; /* undecided */
	int i;

	if (!el->nr)
		return NULL;	/* undefined */

	for (i = el->nr - 1; 0 <= i; i--) {
		struct exclude *x = el->excludes[i];
		const char *exclude = x->pattern;
		int prefix = x->nowildcardlen;

		if (x->flags & EXC_FLAG_MUSTBEDIR) {
			if (*dtype == DT_UNKNOWN)
				*dtype = get_dtype(NULL, istate, pathname, pathlen);
			if (*dtype != DT_DIR)
				continue;
		}

		if (x->flags & EXC_FLAG_NODIR) {
			if (match_basename(basename,
					   pathlen - (basename - pathname),
					   exclude, prefix, x->patternlen,
					   x->flags)) {
				exc = x;
				break;
			}
			continue;
		}

		assert(x->baselen == 0 || x->base[x->baselen - 1] == '/');
		if (match_pathname(pathname, pathlen,
				   x->base, x->baselen ? x->baselen - 1 : 0,
				   exclude, prefix, x->patternlen, x->flags)) {
			exc = x;
			break;
		}
	}
	return exc;
}