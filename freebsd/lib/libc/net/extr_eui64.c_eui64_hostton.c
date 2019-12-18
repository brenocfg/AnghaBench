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
struct eui64 {int dummy; } ;
typedef  int /*<<< orphan*/  local_host ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  _PATH_EUI64 ; 
 int /*<<< orphan*/  bcopy (struct eui64*,struct eui64*,int) ; 
 scalar_t__ eui64_line (char*,struct eui64*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ yp_get_default_domain (char**) ; 
 scalar_t__ yp_match (char*,char*,char const*,int /*<<< orphan*/ ,char**,int*) ; 

int
eui64_hostton(const char *hostname, struct eui64 *id)
{
	FILE *fp;
	char buf[BUFSIZ + 2];
	struct eui64 local_eui64;
	char local_host[MAXHOSTNAMELEN];
#ifdef YP
	char *result;
	int resultlen;
	char *yp_domain;
#endif
	if ((fp = fopen(_PATH_EUI64, "re")) == NULL)
		return (1);

	while (fgets(buf,BUFSIZ,fp)) {
		if (buf[0] == '#')
			continue;
#ifdef YP
		if (buf[0] == '+') {
			if (yp_get_default_domain(&yp_domain))
				continue;
			if (yp_match(yp_domain, "eui64.byname", hostname,
				strlen(hostname), &result, &resultlen)) {
				continue;
			}
			strncpy(buf, result, resultlen);
			buf[resultlen] = '\0';
			free(result);
		}
#endif
		if (eui64_line(buf, &local_eui64, local_host,
		    sizeof(local_host)) == 0) {
			if (strcmp(hostname, local_host) == 0) {
				/* We have a match */
				bcopy(&local_eui64, id, sizeof(struct eui64));
				fclose(fp);
				return(0);
			}
		}
	}
	fclose(fp);
	return (1);
}