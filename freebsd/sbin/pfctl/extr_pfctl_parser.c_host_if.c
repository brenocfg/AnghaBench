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
struct node_host {struct node_host* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int PFI_AFLAG_BROADCAST ; 
 int PFI_AFLAG_MODEMASK ; 
 int PFI_AFLAG_NETWORK ; 
 int PFI_AFLAG_NOALIAS ; 
 int PFI_AFLAG_PEER ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ifa_exists (char*) ; 
 struct node_host* ifa_lookup (char*,int) ; 
 int /*<<< orphan*/  set_ipmask (struct node_host*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

struct node_host *
host_if(const char *s, int mask)
{
	struct node_host	*n, *h = NULL;
	char			*p, *ps;
	int			 flags = 0;

	if ((ps = strdup(s)) == NULL)
		err(1, "host_if: strdup");
	while ((p = strrchr(ps, ':')) != NULL) {
		if (!strcmp(p+1, "network"))
			flags |= PFI_AFLAG_NETWORK;
		else if (!strcmp(p+1, "broadcast"))
			flags |= PFI_AFLAG_BROADCAST;
		else if (!strcmp(p+1, "peer"))
			flags |= PFI_AFLAG_PEER;
		else if (!strcmp(p+1, "0"))
			flags |= PFI_AFLAG_NOALIAS;
		else {
			free(ps);
			return (NULL);
		}
		*p = '\0';
	}
	if (flags & (flags - 1) & PFI_AFLAG_MODEMASK) { /* Yep! */
		fprintf(stderr, "illegal combination of interface modifiers\n");
		free(ps);
		return (NULL);
	}
	if ((flags & (PFI_AFLAG_NETWORK|PFI_AFLAG_BROADCAST)) && mask > -1) {
		fprintf(stderr, "network or broadcast lookup, but "
		    "extra netmask given\n");
		free(ps);
		return (NULL);
	}
	if (ifa_exists(ps) || !strncmp(ps, "self", IFNAMSIZ)) {
		/* interface with this name exists */
		h = ifa_lookup(ps, flags);
		for (n = h; n != NULL && mask > -1; n = n->next)
			set_ipmask(n, mask);
	}

	free(ps);
	return (h);
}