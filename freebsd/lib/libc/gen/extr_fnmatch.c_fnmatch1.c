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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  strmbs ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  bt_strmbs ;

/* Variables and functions */
#define  EOS 131 
 int FNM_CASEFOLD ; 
 int FNM_LEADING_DIR ; 
 int FNM_NOESCAPE ; 
 int FNM_NOMATCH ; 
 int FNM_PATHNAME ; 
 int FNM_PERIOD ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
#define  RANGE_ERROR 130 
#define  RANGE_MATCH 129 
#define  RANGE_NOMATCH 128 
 size_t mbrtowc (int*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rangematch (char const*,int,int,char**,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  towlower (int) ; 

__attribute__((used)) static int
fnmatch1(const char *pattern, const char *string, const char *stringstart,
    int flags, mbstate_t patmbs, mbstate_t strmbs)
{
	const char *bt_pattern, *bt_string;
	mbstate_t bt_patmbs, bt_strmbs;
	char *newp;
	char c;
	wchar_t pc, sc;
	size_t pclen, sclen;

	bt_pattern = bt_string = NULL;
	for (;;) {
		pclen = mbrtowc(&pc, pattern, MB_LEN_MAX, &patmbs);
		if (pclen == (size_t)-1 || pclen == (size_t)-2)
			return (FNM_NOMATCH);
		pattern += pclen;
		sclen = mbrtowc(&sc, string, MB_LEN_MAX, &strmbs);
		if (sclen == (size_t)-1 || sclen == (size_t)-2) {
			sc = (unsigned char)*string;
			sclen = 1;
			memset(&strmbs, 0, sizeof(strmbs));
		}
		switch (pc) {
		case EOS:
			if ((flags & FNM_LEADING_DIR) && sc == '/')
				return (0);
			if (sc == EOS)
				return (0);
			goto backtrack;
		case '?':
			if (sc == EOS)
				return (FNM_NOMATCH);
			if (sc == '/' && (flags & FNM_PATHNAME))
				goto backtrack;
			if (sc == '.' && (flags & FNM_PERIOD) &&
			    (string == stringstart ||
			    ((flags & FNM_PATHNAME) && *(string - 1) == '/')))
				goto backtrack;
			string += sclen;
			break;
		case '*':
			c = *pattern;
			/* Collapse multiple stars. */
			while (c == '*')
				c = *++pattern;

			if (sc == '.' && (flags & FNM_PERIOD) &&
			    (string == stringstart ||
			    ((flags & FNM_PATHNAME) && *(string - 1) == '/')))
				goto backtrack;

			/* Optimize for pattern with * at end or before /. */
			if (c == EOS)
				if (flags & FNM_PATHNAME)
					return ((flags & FNM_LEADING_DIR) ||
					    strchr(string, '/') == NULL ?
					    0 : FNM_NOMATCH);
				else
					return (0);
			else if (c == '/' && flags & FNM_PATHNAME) {
				if ((string = strchr(string, '/')) == NULL)
					return (FNM_NOMATCH);
				break;
			}

			/*
			 * First try the shortest match for the '*' that
			 * could work. We can forget any earlier '*' since
			 * there is no way having it match more characters
			 * can help us, given that we are already here.
			 */
			bt_pattern = pattern, bt_patmbs = patmbs;
			bt_string = string, bt_strmbs = strmbs;
			break;
		case '[':
			if (sc == EOS)
				return (FNM_NOMATCH);
			if (sc == '/' && (flags & FNM_PATHNAME))
				goto backtrack;
			if (sc == '.' && (flags & FNM_PERIOD) &&
			    (string == stringstart ||
			    ((flags & FNM_PATHNAME) && *(string - 1) == '/')))
				goto backtrack;

			switch (rangematch(pattern, sc, flags, &newp,
			    &patmbs)) {
			case RANGE_ERROR:
				goto norm;
			case RANGE_MATCH:
				pattern = newp;
				break;
			case RANGE_NOMATCH:
				goto backtrack;
			}
			string += sclen;
			break;
		case '\\':
			if (!(flags & FNM_NOESCAPE)) {
				pclen = mbrtowc(&pc, pattern, MB_LEN_MAX,
				    &patmbs);
				if (pclen == 0 || pclen == (size_t)-1 ||
				    pclen == (size_t)-2)
					return (FNM_NOMATCH);
				pattern += pclen;
			}
			/* FALLTHROUGH */
		default:
		norm:
			string += sclen;
			if (pc == sc)
				;
			else if ((flags & FNM_CASEFOLD) &&
				 (towlower(pc) == towlower(sc)))
				;
			else {
		backtrack:
				/*
				 * If we have a mismatch (other than hitting
				 * the end of the string), go back to the last
				 * '*' seen and have it match one additional
				 * character.
				 */
				if (bt_pattern == NULL)
					return (FNM_NOMATCH);
				sclen = mbrtowc(&sc, bt_string, MB_LEN_MAX,
				    &bt_strmbs);
				if (sclen == (size_t)-1 ||
				    sclen == (size_t)-2) {
					sc = (unsigned char)*bt_string;
					sclen = 1;
					memset(&bt_strmbs, 0,
					    sizeof(bt_strmbs));
				}
				if (sc == EOS)
					return (FNM_NOMATCH);
				if (sc == '/' && flags & FNM_PATHNAME)
					return (FNM_NOMATCH);
				bt_string += sclen;
				pattern = bt_pattern, patmbs = bt_patmbs;
				string = bt_string, strmbs = bt_strmbs;
			}
			break;
		}
	}
	/* NOTREACHED */
}