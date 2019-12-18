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
struct ether_addr {int /*<<< orphan*/ * octet; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZ ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  _PATH_ETHERS ; 
 int /*<<< orphan*/  bcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ether_line (char*,struct ether_addr*,char*) ; 
 char* ether_ntoa (struct ether_addr const*) ; 
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
ether_ntohost(char *hostname, const struct ether_addr *e)
{
	FILE *fp;
	char buf[BUFSIZ + 2];
	struct ether_addr local_ether;
	char local_host[MAXHOSTNAMELEN];
#ifdef YP
	char *result;
	int resultlen;
	char *ether_a;
	char *yp_domain;
#endif

	if ((fp = fopen(_PATH_ETHERS, "re")) == NULL)
		return (1);
	while (fgets(buf,BUFSIZ,fp)) {
		if (buf[0] == '#')
			continue;
#ifdef YP
		if (buf[0] == '+') {
			if (yp_get_default_domain(&yp_domain))
				continue;
			ether_a = ether_ntoa(e);
			if (yp_match(yp_domain, "ethers.byaddr", ether_a,
			    strlen(ether_a), &result, &resultlen)) {
				continue;
			}
			strncpy(buf, result, resultlen);
			buf[resultlen] = '\0';
			free(result);
		}
#endif
		if (!ether_line(buf, &local_ether, local_host)) {
			if (!bcmp((char *)&local_ether.octet[0],
			    (char *)&e->octet[0], 6)) {
				/* We have a match. */
				strcpy(hostname, local_host);
				fclose(fp);
				return(0);
			}
		}
	}
	fclose(fp);
	return (1);
}