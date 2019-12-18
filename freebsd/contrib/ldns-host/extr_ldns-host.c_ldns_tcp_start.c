#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  scalar_t__ ldns_status ;
struct TYPE_5__ {int /*<<< orphan*/  _socket; int /*<<< orphan*/ * _nameservers; } ;
typedef  TYPE_1__ ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_ADDRESS_ERR ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_NETWORK_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_pkt2buffer_wire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sockaddr_storage* ldns_rdf2native_sockaddr_storage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  ldns_resolver_port (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_resolver_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_tcp_connect (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_tcp_send_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ldns_status
ldns_tcp_start(ldns_resolver *res, ldns_pkt *qpkt, int nameserver) {
    /* This routine is based on ldns_axfr_start, with the major
     * difference in that it takes a query packet explicitly.
     */
    struct sockaddr_storage *ns = NULL;
    size_t ns_len = 0;
    ldns_buffer *qbuf = NULL;
    ldns_status status;

    ns = ldns_rdf2native_sockaddr_storage(
            res->_nameservers[nameserver], ldns_resolver_port(res), &ns_len);
    if (ns == NULL) {
        status = LDNS_STATUS_MEM_ERR;
        goto error;
    }

    res->_socket = ldns_tcp_connect(
            ns, (socklen_t)ns_len, ldns_resolver_timeout(res));
    if (res->_socket <= 0) {
        status = LDNS_STATUS_ADDRESS_ERR;
        goto error;
    }

    qbuf = ldns_buffer_new(LDNS_MAX_PACKETLEN);
    if (qbuf == NULL) {
        status = LDNS_STATUS_MEM_ERR;
        goto error;
    }

    status = ldns_pkt2buffer_wire(qbuf, qpkt);
    if (status != LDNS_STATUS_OK)
        goto error;

    if (ldns_tcp_send_query(qbuf, res->_socket, ns, (socklen_t)ns_len) == 0) {
        status = LDNS_STATUS_NETWORK_ERR;
        goto error;
    }

    ldns_buffer_free(qbuf);
    free(ns);
    return LDNS_STATUS_OK;
 
error:
    ldns_buffer_free(qbuf);
    free(ns);
    if (res->_socket > 0) {
        close(res->_socket);
        res->_socket = 0;
    }
    return status;
}