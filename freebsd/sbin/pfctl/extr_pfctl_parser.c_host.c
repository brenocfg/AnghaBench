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
struct node_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct node_host* host_dns (char*,int,int) ; 
 struct node_host* host_if (char*,int) ; 
 struct node_host* host_v4 (char const*,int) ; 
 struct node_host* host_v6 (char*,int) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

struct node_host *
host(const char *s)
{
	struct node_host	*h = NULL;
	int			 mask, v4mask, v6mask, cont = 1;
	char			*p, *q, *ps;

	if ((p = strrchr(s, '/')) != NULL) {
		mask = strtol(p+1, &q, 0);
		if (!q || *q || mask > 128 || q == (p+1)) {
			fprintf(stderr, "invalid netmask '%s'\n", p);
			return (NULL);
		}
		if ((ps = malloc(strlen(s) - strlen(p) + 1)) == NULL)
			err(1, "host: malloc");
		strlcpy(ps, s, strlen(s) - strlen(p) + 1);
		v4mask = v6mask = mask;
	} else {
		if ((ps = strdup(s)) == NULL)
			err(1, "host: strdup");
		v4mask = 32;
		v6mask = 128;
		mask = -1;
	}

	/* interface with this name exists? */
	if (cont && (h = host_if(ps, mask)) != NULL)
		cont = 0;

	/* IPv4 address? */
	if (cont && (h = host_v4(s, mask)) != NULL)
		cont = 0;

	/* IPv6 address? */
	if (cont && (h = host_v6(ps, v6mask)) != NULL)
		cont = 0;

	/* dns lookup */
	if (cont && (h = host_dns(ps, v4mask, v6mask)) != NULL)
		cont = 0;
	free(ps);

	if (h == NULL || cont == 1) {
		fprintf(stderr, "no IP address found for %s\n", s);
		return (NULL);
	}
	return (h);
}