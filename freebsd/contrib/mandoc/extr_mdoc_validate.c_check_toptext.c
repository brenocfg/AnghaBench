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
struct roff_man {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_BX ; 
 int /*<<< orphan*/  MANDOCERR_FUNC ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,...) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void
check_toptext(struct roff_man *mdoc, int ln, int pos, const char *p)
{
	const char	*cp, *cpr;

	if (*p == '\0')
		return;

	if ((cp = strstr(p, "OpenBSD")) != NULL)
		mandoc_msg(MANDOCERR_BX, ln, pos + (int)(cp - p), "Ox");
	if ((cp = strstr(p, "NetBSD")) != NULL)
		mandoc_msg(MANDOCERR_BX, ln, pos + (int)(cp - p), "Nx");
	if ((cp = strstr(p, "FreeBSD")) != NULL)
		mandoc_msg(MANDOCERR_BX, ln, pos + (int)(cp - p), "Fx");
	if ((cp = strstr(p, "DragonFly")) != NULL)
		mandoc_msg(MANDOCERR_BX, ln, pos + (int)(cp - p), "Dx");

	cp = p;
	while ((cp = strstr(cp + 1, "()")) != NULL) {
		for (cpr = cp - 1; cpr >= p; cpr--)
			if (*cpr != '_' && !isalnum((unsigned char)*cpr))
				break;
		if ((cpr < p || *cpr == ' ') && cpr + 1 < cp) {
			cpr++;
			mandoc_msg(MANDOCERR_FUNC, ln, pos + (int)(cpr - p),
			    "%.*s()", (int)(cp - cpr), cpr);
		}
	}
}