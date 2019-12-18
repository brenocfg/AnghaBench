#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sqls_data {int auth_state; int query_state; } ;
struct TYPE_4__ {int total_bytes; int unprocessed_bytes; } ;
struct TYPE_3__ {int total_bytes; int unprocessed_bytes; } ;
struct connection {scalar_t__ basic_type; int fd; int remote_port; int flags; int status; int error; int generation; int skip_bytes; int pending_queries; int ready; int parse_state; double last_response_time; double last_query_sent_time; struct connection* next; TYPE_2__ Out; TYPE_1__ In; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  type; } ;
struct conn_target {scalar_t__ min_connections; struct connection* first_conn; int /*<<< orphan*/  active_outbound_connections; } ;

/* Variables and functions */
 struct connection* Connections ; 
 int MAX_CONNECTIONS ; 
 scalar_t__ MAX_RES ; 
 scalar_t__ R ; 
 scalar_t__ R_end ; 
 struct sqls_data* SQLS_DATA (struct connection*) ; 
 int STATS_BUFF_SIZE ; 
 struct conn_target* Targets ; 
 int allocated_targets ; 
 int /*<<< orphan*/  assert (struct conn_target*) ; 
 scalar_t__ ct_inbound ; 
 scalar_t__ ct_outbound ; 
 int db_proxy_prepare_stats (struct connection*) ; 
 int /*<<< orphan*/  dbp_get_bad_targets (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  dbp_get_connections (struct connection*,char const*,int) ; 
 int /*<<< orphan*/  dbp_get_targets (struct connection*,char const*,int) ; 
 scalar_t__ dump_outbound_connection (struct connection*,scalar_t__,int) ; 
 int /*<<< orphan*/  return_one_key (struct connection*,char const*,scalar_t__,int) ; 
 char* show_ip (int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (scalar_t__,int,char*,int,char*,int,int,int,int,int,int,scalar_t__,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,double,double) ; 
 scalar_t__ stats_buff ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

int mc_db_proxy_get (struct connection *c, const char *key, int len) {
  if (len >= 5 && !strncmp (key, "stats", 5)) {
    int len = db_proxy_prepare_stats (c);
    return_one_key (c, key, stats_buff, len);
    return 0;
  }

  if (len >= 8 && !strncmp (key, "#inbound", 8)) {
    int i, ptr = 0;
    for (i = 0; i < MAX_CONNECTIONS; i++) {
      struct connection *c = &Connections[i];
      if (c->basic_type == ct_inbound && ptr < STATS_BUFF_SIZE - 1024) {
        struct sqls_data *D = SQLS_DATA(c);
        ptr += snprintf (stats_buff + ptr, STATS_BUFF_SIZE - 6 - ptr,
                         "fd = %d, %s:%d, flags = %d , status = %d, err = %d, gen = %d, skip = %d, basic_type = %d\n"
                         "  Inb = %d + %d, Outb = %d + %d, pend = %d, ready = %d, parse_state=%d, type = %p\n"
                         "  auth state = %d, packet_state = %d\n"
                         "  last_response_time = %.6f, last_query_time = %.6f\n",
                         c->fd, show_ip (c->remote_ip), c->remote_port, c->flags, c->status, c->error, c->generation, c->skip_bytes, c->basic_type,
                         c->In.total_bytes, c->In.unprocessed_bytes, c->Out.total_bytes, c->Out.unprocessed_bytes,
                         c->pending_queries, c->ready, c->parse_state, c->type, 
                         D->auth_state, D->query_state,
                         c->last_response_time, c->last_query_sent_time);


      }
    }
    return_one_key (c, key, stats_buff, ptr);
    return 0;
  }

  if (len >= 9 && !strncmp (key, "#outbound", 9)) {
    int i, ptr = 0;
    for (i = 0; i < MAX_CONNECTIONS; i++) {
      struct connection *c = &Connections[i];
      if (c->basic_type == ct_outbound && ptr < STATS_BUFF_SIZE - 1024) {
        ptr += dump_outbound_connection (c, stats_buff + ptr, STATS_BUFF_SIZE - 6 - ptr);
      }
    }
    return_one_key (c, key, stats_buff, ptr);
    return 0;
  }

    
  if (!strcmp (key, "#bad_targets")) {
    dbp_get_bad_targets (c, key, len);
    return 0;
  }

  if (!strcmp (key, "#bad_connections")) {
    int i, ptr = 0;
    for (i = 0; i < allocated_targets && R_end < R + MAX_RES; i++) {
      struct conn_target *S = &Targets[i];
      assert (S);
      if (S->min_connections > 0 && !S->active_outbound_connections) {
        struct connection *c;
        for (c = S->first_conn; c != (struct connection *)S; c = c->next) {
          if (c->basic_type == ct_outbound && ptr < STATS_BUFF_SIZE - 1024) {
            ptr += dump_outbound_connection (c, stats_buff + ptr, STATS_BUFF_SIZE - 6 - ptr);
          }
        }
      }
    }
    return_one_key (c, key, stats_buff, ptr);
    return 0;
  }

  if (!strcmp (key, "#targets")) {
    dbp_get_targets (c, key, len);
    return 0;
  } 
  
  if (!strcmp (key, "#connections")) {
    dbp_get_connections (c, key, len);
    return 0;
  } 
  
  return 0;
}