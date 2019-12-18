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
struct st_h2o_http3client_conn_t {int /*<<< orphan*/ * getaddr_req; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  h2o_hostinfo_getaddr_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 struct addrinfo* h2o_hostinfo_select_one (struct addrinfo*) ; 
 int /*<<< orphan*/  start_connect (struct st_h2o_http3client_conn_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_getaddr(h2o_hostinfo_getaddr_req_t *getaddr_req, const char *errstr, struct addrinfo *res, void *_conn)
{
    struct st_h2o_http3client_conn_t *conn = _conn;

    assert(getaddr_req == conn->getaddr_req);
    conn->getaddr_req = NULL;

    if (errstr != NULL) {
        /* TODO reconnect */
        abort();
    }

    struct addrinfo *selected = h2o_hostinfo_select_one(res);
    start_connect(conn, selected->ai_addr, selected->ai_addrlen);
}