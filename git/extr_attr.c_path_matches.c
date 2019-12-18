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
struct pattern {char* pattern; int nowildcardlen; int flags; int /*<<< orphan*/  patternlen; } ;

/* Variables and functions */
 int PATTERN_FLAG_MUSTBEDIR ; 
 int PATTERN_FLAG_NODIR ; 
 int match_basename (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 int match_pathname (char const*,int,char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int path_matches(const char *pathname, int pathlen,
			int basename_offset,
			const struct pattern *pat,
			const char *base, int baselen)
{
	const char *pattern = pat->pattern;
	int prefix = pat->nowildcardlen;
	int isdir = (pathlen && pathname[pathlen - 1] == '/');

	if ((pat->flags & PATTERN_FLAG_MUSTBEDIR) && !isdir)
		return 0;

	if (pat->flags & PATTERN_FLAG_NODIR) {
		return match_basename(pathname + basename_offset,
				      pathlen - basename_offset - isdir,
				      pattern, prefix,
				      pat->patternlen, pat->flags);
	}
	return match_pathname(pathname, pathlen - isdir,
			      base, baselen,
			      pattern, prefix, pat->patternlen, pat->flags);
}