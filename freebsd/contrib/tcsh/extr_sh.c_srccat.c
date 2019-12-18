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
typedef  char Char ;

/* Variables and functions */
 char* Strend (char*) ; 
 char* Strspl (char*,char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 scalar_t__ mflag ; 
 char* short2str (char*) ; 
 int srcfile (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static int
srccat(Char *cp, Char *dp)
{
    if (cp[0] == '/' && cp[1] == '\0') 
	return srcfile(short2str(dp), (mflag ? 0 : 1), 0, NULL);
    else {
	Char *ep;
	char   *ptr;
	int rv;

#ifdef WINNT_NATIVE
	ep = Strend(cp);
	if (ep != cp && ep[-1] == '/' && dp[0] == '/') /* silly win95 */
	    dp++;
#endif /* WINNT_NATIVE */

	ep = Strspl(cp, dp);
	cleanup_push(ep, xfree);
	ptr = short2str(ep);

	rv = srcfile(ptr, (mflag ? 0 : 1), 0, NULL);
	cleanup_until(ep);
	return rv;
    }
}