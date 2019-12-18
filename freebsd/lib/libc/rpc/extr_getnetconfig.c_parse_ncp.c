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
struct netconfig {char** nc_lookups; scalar_t__ nc_nlookups; int /*<<< orphan*/ * nc_device; int /*<<< orphan*/ * nc_proto; int /*<<< orphan*/ * nc_protofmly; int /*<<< orphan*/  nc_flag; int /*<<< orphan*/  nc_semantics; int /*<<< orphan*/ * nc_netid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NC_BADFILE ; 
 int /*<<< orphan*/  NC_BROADCAST ; 
#define  NC_BROADCAST_C 130 
 int /*<<< orphan*/  NC_NOFLAG ; 
#define  NC_NOFLAG_C 129 
 int /*<<< orphan*/  NC_NOLOOKUP ; 
 int /*<<< orphan*/  NC_TPI_CLTS ; 
 int /*<<< orphan*/  NC_TPI_CLTS_S ; 
 int /*<<< orphan*/  NC_TPI_COTS ; 
 int /*<<< orphan*/  NC_TPI_COTS_ORD ; 
 int /*<<< orphan*/  NC_TPI_COTS_ORD_S ; 
 int /*<<< orphan*/  NC_TPI_COTS_S ; 
 int /*<<< orphan*/  NC_TPI_RAW ; 
 int /*<<< orphan*/  NC_TPI_RAW_S ; 
 int /*<<< orphan*/  NC_VISIBLE ; 
#define  NC_VISIBLE_C 128 
 char* _get_next_token (char*,char) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  nc_error ; 
 char** reallocarray (char**,scalar_t__,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 void* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int
parse_ncp(char *stringp, struct netconfig *ncp)
{
    char    *tokenp;	/* for processing tokens */
    char    *lasts;
    char    **nc_lookups;

    nc_error = NC_BADFILE;	/* nearly anything that breaks is for this reason */
    stringp[strlen(stringp)-1] = '\0';	/* get rid of newline */
    /* netid */
    if ((ncp->nc_netid = strtok_r(stringp, "\t ", &lasts)) == NULL) {
	return (-1);
    }

    /* semantics */
    if ((tokenp = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    if (strcmp(tokenp, NC_TPI_COTS_ORD_S) == 0)
	ncp->nc_semantics = NC_TPI_COTS_ORD;
    else if (strcmp(tokenp, NC_TPI_COTS_S) == 0)
	ncp->nc_semantics = NC_TPI_COTS;
    else if (strcmp(tokenp, NC_TPI_CLTS_S) == 0)
	ncp->nc_semantics = NC_TPI_CLTS;
    else if (strcmp(tokenp, NC_TPI_RAW_S) == 0)
	ncp->nc_semantics = NC_TPI_RAW;
    else
	return (-1);

    /* flags */
    if ((tokenp = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    for (ncp->nc_flag = NC_NOFLAG; *tokenp != '\0';
	    tokenp++) {
	switch (*tokenp) {
	case NC_NOFLAG_C:
	    break;
	case NC_VISIBLE_C:
	    ncp->nc_flag |= NC_VISIBLE;
	    break;
	case NC_BROADCAST_C:
	    ncp->nc_flag |= NC_BROADCAST;
	    break;
	default:
	    return (-1);
	}
    }
    /* protocol family */
    if ((ncp->nc_protofmly = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    /* protocol name */
    if ((ncp->nc_proto = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    /* network device */
    if ((ncp->nc_device = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    if ((tokenp = strtok_r(NULL, "\t ", &lasts)) == NULL) {
	return (-1);
    }
    if (strcmp(tokenp, NC_NOLOOKUP) == 0) {
	ncp->nc_nlookups = 0;
	ncp->nc_lookups = NULL;
    } else {
	char *cp;	    /* tmp string */

	free(ncp->nc_lookups); /* from last visit */
	ncp->nc_lookups = NULL;
	ncp->nc_nlookups = 0;
	while ((cp = tokenp) != NULL) {
	    if ((nc_lookups = reallocarray(ncp->nc_lookups,
		ncp->nc_nlookups + 1, sizeof(*ncp->nc_lookups))) == NULL) {
		    free(ncp->nc_lookups);
		    ncp->nc_lookups = NULL;
		    return (-1);
	    }
	    tokenp = _get_next_token(cp, ',');
	    ncp->nc_lookups = nc_lookups;
	    ncp->nc_lookups[ncp->nc_nlookups++] = cp;
	}
    }
    return (0);
}