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
struct lc_messages_T {int /*<<< orphan*/ * nostr; int /*<<< orphan*/ * yesstr; } ;
struct xlocale_messages {int /*<<< orphan*/  buffer; struct lc_messages_T locale; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCMESSAGES_SIZE_FULL ; 
 int /*<<< orphan*/  LCMESSAGES_SIZE_MIN ; 
 int _LDP_LOADED ; 
 int __part_load_locale (char const*,int*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 void* empty ; 

__attribute__((used)) static int
messages_load_locale(struct xlocale_messages *loc, int *using_locale, const char *name)
{
	int ret;
	struct lc_messages_T *l = &loc->locale;

	ret = __part_load_locale(name, using_locale,
		  &loc->buffer, "LC_MESSAGES",
		  LCMESSAGES_SIZE_FULL, LCMESSAGES_SIZE_MIN,
		  (const char **)l);
	if (ret == _LDP_LOADED) {
		if (l->yesstr == NULL)
			l->yesstr = empty;
		if (l->nostr == NULL)
			l->nostr = empty;
	}
	return (ret);
}