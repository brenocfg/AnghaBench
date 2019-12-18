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
struct url_ent {int dummy; } ;
struct url {int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEME_FILE ; 
 int /*<<< orphan*/  SCHEME_FTP ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 int /*<<< orphan*/  SCHEME_HTTPS ; 
 int /*<<< orphan*/  URL_BAD_SCHEME ; 
 struct url_ent* fetchListFTP (struct url*,char const*) ; 
 struct url_ent* fetchListFile (struct url*,char const*) ; 
 struct url_ent* fetchListHTTP (struct url*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  url_seterr (int /*<<< orphan*/ ) ; 

struct url_ent *
fetchList(struct url *URL, const char *flags)
{

	if (strcmp(URL->scheme, SCHEME_FILE) == 0)
		return (fetchListFile(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_FTP) == 0)
		return (fetchListFTP(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTP) == 0)
		return (fetchListHTTP(URL, flags));
	else if (strcmp(URL->scheme, SCHEME_HTTPS) == 0)
		return (fetchListHTTP(URL, flags));
	url_seterr(URL_BAD_SCHEME);
	return (NULL);
}