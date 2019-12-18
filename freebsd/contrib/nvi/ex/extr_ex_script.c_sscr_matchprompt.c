#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* script; } ;
struct TYPE_4__ {size_t sh_prompt_len; char* sh_prompt; } ;
typedef  TYPE_1__ SCRIPT ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */

__attribute__((used)) static int
sscr_matchprompt(SCR *sp, char *lp, size_t line_len, size_t *lenp)
{
	SCRIPT *sc;
	size_t prompt_len;
	char *pp;

	sc = sp->script;
	if (line_len < (prompt_len = sc->sh_prompt_len))
		return (0);

	for (pp = sc->sh_prompt;
	    prompt_len && line_len; --prompt_len, --line_len) {
		if (*pp == '\0') {
			for (; prompt_len && *pp == '\0'; --prompt_len, ++pp);
			if (!prompt_len)
				return (0);
			for (; line_len && *lp != *pp; --line_len, ++lp);
			if (!line_len)
				return (0);
		}
		if (*pp++ != *lp++)
			break;
	}

	if (prompt_len)
		return (0);
	if (lenp != NULL)
		*lenp = line_len;
	return (1);
}