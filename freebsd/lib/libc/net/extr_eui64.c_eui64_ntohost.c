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
struct eui64 {int /*<<< orphan*/ * octet; } ;
typedef  int /*<<< orphan*/  local_host ;
typedef  int /*<<< orphan*/  eui64_a ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int /*<<< orphan*/  EUI64_LEN ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  _PATH_EUI64 ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eui64_line (char*,struct eui64*,char*,int) ; 
 int /*<<< orphan*/  eui64_ntoa (struct eui64 const*,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ yp_get_default_domain (char**) ; 
 scalar_t__ yp_match (char*,char*,char*,int /*<<< orphan*/ ,char**,int*) ; 

int
eui64_ntohost(char *hostname, size_t len, const struct eui64 *id)
{
	FILE *fp;
	char buf[BUFSIZ + 2];
	struct eui64 local_eui64;
	char local_host[MAXHOSTNAMELEN];
#ifdef YP
	char *result;
	int resultlen;
	char eui64_a[24];
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
			eui64_ntoa(id, eui64_a, sizeof(eui64_a));
			if (yp_match(yp_domain, "eui64.byid", eui64_a,
				strlen(eui64_a), &result, &resultlen)) {
				continue;
			}
			strncpy(buf, result, resultlen);
			buf[resultlen] = '\0';
			free(result);
		}
#endif
		if (eui64_line(buf, &local_eui64, local_host,
		    sizeof(local_host)) == 0) {
			if (bcmp(&local_eui64.octet[0],
				&id->octet[0], EUI64_LEN) == 0) {
			/* We have a match */
				strcpy(hostname, local_host);
				fclose(fp);
				return(0);
			}
		}
	}
	fclose(fp);
	return (1);
}