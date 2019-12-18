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
struct rpc_server {scalar_t__ sfd; scalar_t__ parse_status; int /*<<< orphan*/  parse_len; int /*<<< orphan*/  parse_buf; } ;

/* Variables and functions */
 scalar_t__ buffer_create (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_delete (scalar_t__) ; 
 scalar_t__ error_verbosity ; 
 int /*<<< orphan*/  first_qid ; 
 int /*<<< orphan*/  global_generation ; 
 scalar_t__ inbuf ; 
 scalar_t__ last_connection_fd ; 
 int /*<<< orphan*/  last_qid ; 
 int last_server_fd ; 
 scalar_t__ max_query_id ; 
 scalar_t__ outbuf ; 
 scalar_t__ parse_status_reading_query ; 
 struct rpc_server** servers ; 
 int /*<<< orphan*/  tl_parse_on_rinit () ; 
 int /*<<< orphan*/  zzemalloc (int /*<<< orphan*/ ) ; 

void rpc_on_rinit (int module_number) { /* {{{ */
  global_generation ++;
  error_verbosity = 0;
  if (inbuf) {
    inbuf = buffer_delete (inbuf);
  }
  if (outbuf) {
    outbuf = buffer_delete (outbuf);
  }
  outbuf = buffer_create (0);
  first_qid = last_qid;
  max_query_id = 0;
  int i;
  for (i = 0; i < last_server_fd; i++) {
    struct rpc_server *server = servers[i];
    if (server->sfd >= 0) {
      if (server->parse_status == parse_status_reading_query) {
        server->parse_buf = zzemalloc (server->parse_len);
      }
    }
  }
  last_connection_fd = 0;
  tl_parse_on_rinit ();
}