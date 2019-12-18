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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  NOEXPR ; 
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  YESEXPR ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

int
rpmatch(const char *response)
{
	regex_t yes, no;
	int ret;

	if (regcomp(&yes, nl_langinfo(YESEXPR), REG_EXTENDED|REG_NOSUB) != 0)
		return (-1);
	if (regcomp(&no, nl_langinfo(NOEXPR), REG_EXTENDED|REG_NOSUB) != 0) {
		regfree(&yes);
		return (-1);
	}
	if (regexec(&yes, response, 0, NULL, 0) == 0)
		ret = 1;
	else if (regexec(&no, response, 0, NULL, 0) == 0)
		ret = 0;
	else
		ret = -1;
	regfree(&yes);
	regfree(&no);
	return (ret);
}