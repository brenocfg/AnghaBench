#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* line; } ;
struct TYPE_5__ {char const* str; int num; } ;
typedef  TYPE_1__ HistEvent ;
typedef  TYPE_2__ HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  H_CURR ; 
 int /*<<< orphan*/  H_FIRST ; 
 int /*<<< orphan*/  H_SET ; 
 char* el_calloc (size_t,int) ; 
 int /*<<< orphan*/  el_free (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  h ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int history_base ; 
 char const history_expansion_char ; 
 TYPE_2__* history_get (int) ; 
 int history_length ; 
 int history_search (char*,int) ; 
 int history_search_prefix (char*,int) ; 
 char* last_search_match ; 
 char* last_search_pat ; 
 int /*<<< orphan*/  rl_outstream ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

const char *
get_history_event(const char *cmd, int *cindex, int qchar)
{
	int idx, sign, sub, num, begin, ret;
	size_t len;
	char	*pat;
	const char *rptr;
	HistEvent ev;

	idx = *cindex;
	if (cmd[idx++] != history_expansion_char)
		return NULL;

	/* find out which event to take */
	if (cmd[idx] == history_expansion_char || cmd[idx] == '\0') {
		if (history(h, &ev, H_FIRST) != 0)
			return NULL;
		*cindex = cmd[idx]? (idx + 1):idx;
		return ev.str;
	}
	sign = 0;
	if (cmd[idx] == '-') {
		sign = 1;
		idx++;
	}

	if ('0' <= cmd[idx] && cmd[idx] <= '9') {
		HIST_ENTRY *he;

		num = 0;
		while (cmd[idx] && '0' <= cmd[idx] && cmd[idx] <= '9') {
			num = num * 10 + cmd[idx] - '0';
			idx++;
		}
		if (sign)
			num = history_length - num + history_base;

		if (!(he = history_get(num)))
			return NULL;

		*cindex = idx;
		return he->line;
	}
	sub = 0;
	if (cmd[idx] == '?') {
		sub = 1;
		idx++;
	}
	begin = idx;
	while (cmd[idx]) {
		if (cmd[idx] == '\n')
			break;
		if (sub && cmd[idx] == '?')
			break;
		if (!sub && (cmd[idx] == ':' || cmd[idx] == ' '
				    || cmd[idx] == '\t' || cmd[idx] == qchar))
			break;
		idx++;
	}
	len = (size_t)idx - (size_t)begin;
	if (sub && cmd[idx] == '?')
		idx++;
	if (sub && len == 0 && last_search_pat && *last_search_pat)
		pat = last_search_pat;
	else if (len == 0)
		return NULL;
	else {
		if ((pat = el_calloc(len + 1, sizeof(*pat))) == NULL)
			return NULL;
		(void)strncpy(pat, cmd + begin, len);
		pat[len] = '\0';
	}

	if (history(h, &ev, H_CURR) != 0) {
		if (pat != last_search_pat)
			el_free(pat);
		return NULL;
	}
	num = ev.num;

	if (sub) {
		if (pat != last_search_pat) {
			if (last_search_pat)
				el_free(last_search_pat);
			last_search_pat = pat;
		}
		ret = history_search(pat, -1);
	} else
		ret = history_search_prefix(pat, -1);

	if (ret == -1) {
		/* restore to end of list on failed search */
		history(h, &ev, H_FIRST);
		(void)fprintf(rl_outstream, "%s: Event not found\n", pat);
		if (pat != last_search_pat)
			el_free(pat);
		return NULL;
	}

	if (sub && len) {
		if (last_search_match && last_search_match != pat)
			el_free(last_search_match);
		last_search_match = pat;
	}

	if (pat != last_search_pat)
		el_free(pat);

	if (history(h, &ev, H_CURR) != 0)
		return NULL;
	*cindex = idx;
	rptr = ev.str;

	/* roll back to original position */
	(void)history(h, &ev, H_SET, num);

	return rptr;
}