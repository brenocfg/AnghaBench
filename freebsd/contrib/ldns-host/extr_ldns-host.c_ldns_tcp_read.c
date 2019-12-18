#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;
typedef  scalar_t__ ldns_status ;
struct TYPE_4__ {scalar_t__ _socket; } ;
typedef  TYPE_1__ ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_querytime (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_set_timestamp (int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/  ldns_resolver_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/ * ldns_tcp_read_wire_timeout (scalar_t__,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_wire2pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ldns_status
ldns_tcp_read(ldns_pkt **answer, ldns_resolver *res) {
    ldns_status status;
    struct timeval t1, t2;
    uint8_t *data;
    size_t size;

    if (res->_socket <= 0)
        return LDNS_STATUS_ERR;

    gettimeofday(&t1, NULL);
    data = ldns_tcp_read_wire_timeout(
            res->_socket, &size, ldns_resolver_timeout(res));
    if (data == NULL)
        goto error;

    status = ldns_wire2pkt(answer, data, size);
    free(data);
    if (status != LDNS_STATUS_OK)
        goto error;

    gettimeofday(&t2, NULL);
    ldns_pkt_set_querytime(*answer,
            (uint32_t)((t2.tv_sec - t1.tv_sec)*1000) +
                (t2.tv_usec - t1.tv_usec)/1000);
    ldns_pkt_set_timestamp(*answer, t2);
    return status;

error:
    close(res->_socket);
    res->_socket = 0;
    return LDNS_STATUS_ERR;
}