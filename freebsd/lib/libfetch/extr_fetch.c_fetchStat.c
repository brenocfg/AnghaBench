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
struct url_stat {int size; scalar_t__ mtime; scalar_t__ atime; } ;
struct url {int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEME_FILE ; 
 int /*<<< orphan*/  SCHEME_FTP ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 int /*<<< orphan*/  SCHEME_HTTPS ; 
 int /*<<< orphan*/  URL_BAD_SCHEME ; 
 int fetchStatFTP (struct url*,struct url_stat*,char const*) ; 
 int fetchStatFile (struct url*,struct url_stat*,char const*) ; 
 int fetchStatHTTP (struct url*,struct url_stat*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  url_seterr (int /*<<< orphan*/ ) ; 

int
fetchStat(struct url *URL, struct url_stat *us, const char *flags)
{

	if (us != NULL) {
		us->size = -1;
		us->atime = us->mtime = 0;
	}
	if (strcmp(URL->scheme, SCHEME_FILE) == 0)
		return (fetchStatFile(URL, us, flags));
	else if (strcmp(URL->scheme, SCHEME_FTP) == 0)
		return (fetchStatFTP(URL, us, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTP) == 0)
		return (fetchStatHTTP(URL, us, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTPS) == 0)
		return (fetchStatHTTP(URL, us, flags));
	url_seterr(URL_BAD_SCHEME);
	return (-1);
}