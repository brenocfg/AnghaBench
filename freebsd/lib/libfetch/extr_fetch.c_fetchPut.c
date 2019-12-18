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
struct url {int /*<<< orphan*/  scheme; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEME_FILE ; 
 int /*<<< orphan*/  SCHEME_FTP ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 int /*<<< orphan*/  SCHEME_HTTPS ; 
 int /*<<< orphan*/  URL_BAD_SCHEME ; 
 int /*<<< orphan*/ * fetchPutFTP (struct url*,char const*) ; 
 int /*<<< orphan*/ * fetchPutFile (struct url*,char const*) ; 
 int /*<<< orphan*/ * fetchPutHTTP (struct url*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  url_seterr (int /*<<< orphan*/ ) ; 

FILE *
fetchPut(struct url *URL, const char *flags)
{

	if (strcmp(URL->scheme, SCHEME_FILE) == 0)
		return (fetchPutFile(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_FTP) == 0)
		return (fetchPutFTP(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTP) == 0)
		return (fetchPutHTTP(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTPS) == 0)
		return (fetchPutHTTP(URL, flags));
	url_seterr(URL_BAD_SCHEME);
	return (NULL);
}