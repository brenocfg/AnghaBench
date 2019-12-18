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
struct url {int /*<<< orphan*/ * scheme; scalar_t__ port; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEME_FTP ; 
 int /*<<< orphan*/  SCHEME_HTTP ; 
 int /*<<< orphan*/  fetchFreeURL (struct url*) ; 
 struct url* fetchParseURL (char*) ; 
 scalar_t__ fetch_default_proxy_port (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_no_proxy_match (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct url *
ftp_get_proxy(struct url * url, const char *flags)
{
	struct url *purl;
	char *p;

	if (flags != NULL && strchr(flags, 'd') != NULL)
		return (NULL);
	if (fetch_no_proxy_match(url->host))
		return (NULL);
	if (((p = getenv("FTP_PROXY")) || (p = getenv("ftp_proxy")) ||
		(p = getenv("HTTP_PROXY")) || (p = getenv("http_proxy"))) &&
	    *p && (purl = fetchParseURL(p)) != NULL) {
		if (!*purl->scheme) {
			if (getenv("FTP_PROXY") || getenv("ftp_proxy"))
				strcpy(purl->scheme, SCHEME_FTP);
			else
				strcpy(purl->scheme, SCHEME_HTTP);
		}
		if (!purl->port)
			purl->port = fetch_default_proxy_port(purl->scheme);
		if (strcmp(purl->scheme, SCHEME_FTP) == 0 ||
		    strcmp(purl->scheme, SCHEME_HTTP) == 0)
			return (purl);
		fetchFreeURL(purl);
	}
	return (NULL);
}