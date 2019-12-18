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
struct addrinfo {scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int EAI_AGAIN ; 
#define  LDNS_RESOLV_INET 129 
#define  LDNS_RESOLV_INET6 128 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  die (int,char*,char const*,...) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  ldns_get_errorstr_by_id (scalar_t__) ; 
 int ldns_resolver_ip6 (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_sockaddr_storage2rdf (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
resolver_set_nameserver_hostname(ldns_resolver *res, const char *server) {
    struct addrinfo hints, *ailist, *ai;
    ldns_status status;
    ldns_rdf *rdf;
    int err;

    memset(&hints, 0, sizeof hints);
    switch (ldns_resolver_ip6(res)) {
    case LDNS_RESOLV_INET: hints.ai_family = PF_INET; break;
    case LDNS_RESOLV_INET6: hints.ai_family = PF_INET6; break;
    default: hints.ai_family = PF_UNSPEC; break;
    }
    hints.ai_socktype = SOCK_STREAM;
    do err = getaddrinfo(server, NULL, &hints, &ailist);
    while (err == EAI_AGAIN);
    if (err != 0)
        die(1, "couldn't get address for '%s': %s", server, gai_strerror(err));
    for (ai = ailist; ai != NULL; ai = ai->ai_next) {
        if ((rdf = ldns_sockaddr_storage2rdf((void*)ai->ai_addr, NULL)) == NULL)
            die(1, "couldn't allocate an rdf: %s",
                ldns_get_errorstr_by_id(LDNS_STATUS_MEM_ERR));
        status = ldns_resolver_push_nameserver(res, rdf);
        if (status != LDNS_STATUS_OK)
            die(1, "couldn't push a nameserver address: %s",
                ldns_get_errorstr_by_id(status));
    }
}