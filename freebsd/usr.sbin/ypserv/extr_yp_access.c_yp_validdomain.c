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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  dompath ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ YPMAXDOMAIN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 char* yp_dir ; 

int
yp_validdomain(const char *domain)
{
	struct stat statbuf;
	char dompath[MAXPATHLEN + 2];

	if (domain == NULL || strstr(domain, "binding") ||
	    !strcmp(domain, ".") || !strcmp(domain, "..") ||
	    strchr(domain, '/') || strlen(domain) > YPMAXDOMAIN)
		return(1);

	snprintf(dompath, sizeof(dompath), "%s/%s", yp_dir, domain);

	if (stat(dompath, &statbuf) < 0 || !S_ISDIR(statbuf.st_mode))
		return(1);


	return(0);
}