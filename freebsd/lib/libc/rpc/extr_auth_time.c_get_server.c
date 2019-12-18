#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct in_addr {int dummy; } ;
struct hostent {char** h_addr_list; } ;
struct TYPE_12__ {scalar_t__ n_len; int /*<<< orphan*/ * n_bytes; } ;
struct TYPE_11__ {int ep_len; TYPE_5__* ep_val; } ;
struct TYPE_13__ {TYPE_3__ pkey; int /*<<< orphan*/  key_type; TYPE_2__ ep; scalar_t__ name; } ;
typedef  TYPE_4__ nis_server ;
typedef  scalar_t__ nis_name ;
typedef  int /*<<< orphan*/  hname ;
struct TYPE_14__ {int /*<<< orphan*/ * proto; int /*<<< orphan*/ * family; int /*<<< orphan*/ * uaddr; } ;
typedef  TYPE_5__ endpoint ;

/* Variables and functions */
 int /*<<< orphan*/  NIS_PK_NONE ; 
 int /*<<< orphan*/  free_eps (TYPE_5__*,int) ; 
 struct hostent* gethostbyname (char*) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static nis_server *
get_server(struct sockaddr_in *sin, char *host, nis_server *srv,
    endpoint eps[], int maxep)
{
	char			hname[256];
	int			num_ep = 0, i;
	struct hostent		*he;
	struct hostent		dummy;
	char			*ptr[2];
	endpoint		*ep;

	if (host == NULL && sin == NULL)
		return (NULL);

	if (sin == NULL) {
		he = gethostbyname(host);
		if (he == NULL)
			return(NULL);
	} else {
		he = &dummy;
		ptr[0] = (char *)&sin->sin_addr.s_addr;
		ptr[1] = NULL;
		dummy.h_addr_list = ptr;
	}

	/*
	 * This is lame. We go around once for TCP, then again
	 * for UDP.
	 */
	for (i = 0, ep = eps; (he->h_addr_list[i] != NULL) && (num_ep < maxep);
	    i++, ep++, num_ep++) {
		struct in_addr *a;

		a = (struct in_addr *)he->h_addr_list[i];
		snprintf(hname, sizeof(hname), "%s.0.111", inet_ntoa(*a));
		ep->uaddr = strdup(hname);
		ep->family = strdup("inet");
		ep->proto =  strdup("tcp");
		if (ep->uaddr == NULL || ep->family == NULL || ep->proto == NULL) {
			free_eps(eps, num_ep + 1);
			return (NULL);
		}
	}

	for (i = 0; (he->h_addr_list[i] != NULL) && (num_ep < maxep);
	    i++, ep++, num_ep++) {
		struct in_addr *a;

		a = (struct in_addr *)he->h_addr_list[i];
		snprintf(hname, sizeof(hname), "%s.0.111", inet_ntoa(*a));
		ep->uaddr = strdup(hname);
		ep->family = strdup("inet");
		ep->proto =  strdup("udp");
		if (ep->uaddr == NULL || ep->family == NULL || ep->proto == NULL) {
			free_eps(eps, num_ep + 1);
			return (NULL);
		}
	}

	srv->name = (nis_name) host;
	srv->ep.ep_len = num_ep;
	srv->ep.ep_val = eps;
	srv->key_type = NIS_PK_NONE;
	srv->pkey.n_bytes = NULL;
	srv->pkey.n_len = 0;
	return (srv);
}