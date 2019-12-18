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
struct TYPE_3__ {struct ff_regs* find_func_priv; int /*<<< orphan*/  find_func; } ;
typedef  TYPE_1__ xdemitconf_t ;
struct ff_regs {int nr; struct ff_reg* array; } ;
struct ff_reg {int negate; int /*<<< orphan*/  re; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct ff_reg*,int) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  ff_regexp ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 
 struct ff_regs* xmalloc (int) ; 
 char* xstrndup (char const*,int) ; 

void xdiff_set_find_func(xdemitconf_t *xecfg, const char *value, int cflags)
{
	int i;
	struct ff_regs *regs;

	xecfg->find_func = ff_regexp;
	regs = xecfg->find_func_priv = xmalloc(sizeof(struct ff_regs));
	for (i = 0, regs->nr = 1; value[i]; i++)
		if (value[i] == '\n')
			regs->nr++;
	ALLOC_ARRAY(regs->array, regs->nr);
	for (i = 0; i < regs->nr; i++) {
		struct ff_reg *reg = regs->array + i;
		const char *ep = strchr(value, '\n'), *expression;
		char *buffer = NULL;

		reg->negate = (*value == '!');
		if (reg->negate && i == regs->nr - 1)
			die("Last expression must not be negated: %s", value);
		if (*value == '!')
			value++;
		if (ep)
			expression = buffer = xstrndup(value, ep - value);
		else
			expression = value;
		if (regcomp(&reg->re, expression, cflags))
			die("Invalid regexp to look for hunk header: %s", expression);
		free(buffer);
		value = ep + 1;
	}
}