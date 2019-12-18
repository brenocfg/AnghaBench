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
typedef  int /*<<< orphan*/  pw ;
typedef  int /*<<< orphan*/  prompt ;

/* Variables and functions */
 int /*<<< orphan*/  RPP_REQUIRE_TTY ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * readpassphrase (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static const char *
getproxypass(const char *proxyuser, const char *proxyhost)
{
	char prompt[512];
	static char pw[256];

	snprintf(prompt, sizeof(prompt), "Proxy password for %s@%s: ",
	   proxyuser, proxyhost);
	if (readpassphrase(prompt, pw, sizeof(pw), RPP_REQUIRE_TTY) == NULL)
		errx(1, "Unable to read proxy passphrase");
	return (pw);
}