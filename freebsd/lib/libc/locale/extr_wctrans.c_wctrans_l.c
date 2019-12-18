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
typedef  scalar_t__ wctrans_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ _WCT_ERROR ; 
 scalar_t__ _WCT_TOLOWER ; 
 scalar_t__ _WCT_TOUPPER ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strcmp (char const*,char const*) ; 

wctrans_t
wctrans_l(const char *charclass, locale_t locale)
{
	struct {
		const char	*name;
		wctrans_t	 trans;
	} ccls[] = {
		{ "tolower",	_WCT_TOLOWER },
		{ "toupper",	_WCT_TOUPPER },
		{ NULL,		_WCT_ERROR },		/* Default */
	};
	int i;

	i = 0;
	while (ccls[i].name != NULL && strcmp(ccls[i].name, charclass) != 0)
		i++;

	if (ccls[i].trans == _WCT_ERROR)
		errno = EINVAL;
	return (ccls[i].trans);
}