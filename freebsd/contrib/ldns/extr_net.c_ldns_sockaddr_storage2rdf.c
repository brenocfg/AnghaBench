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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  LDNS_IP4ADDRLEN ; 
 int /*<<< orphan*/  LDNS_IP6ADDRLEN ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_AAAA ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

ldns_rdf *
ldns_sockaddr_storage2rdf(const struct sockaddr_storage *sock, uint16_t *port)
{
        ldns_rdf *addr;
        struct sockaddr_in *data_in;
        struct sockaddr_in6 *data_in6;

        switch(sock->ss_family) {
                case AF_INET:
                        data_in = (struct sockaddr_in*)sock;
                        if (port) {
                                *port = ntohs((uint16_t)data_in->sin_port);
                        }
                        addr = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_A,
                                        LDNS_IP4ADDRLEN, &data_in->sin_addr);
                        break;
                case AF_INET6:
                        data_in6 = (struct sockaddr_in6*)sock;
                        if (port) {
                                *port = ntohs((uint16_t)data_in6->sin6_port);
                        }
                        addr = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_AAAA,
                                        LDNS_IP6ADDRLEN, &data_in6->sin6_addr);
                        break;
                default:
                        if (port) {
                                *port = 0;
                        }
                        return NULL;
        }
        return addr;
}