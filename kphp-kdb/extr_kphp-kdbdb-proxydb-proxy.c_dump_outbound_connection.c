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
struct sqlc_data {int auth_state; int response_state; } ;
struct TYPE_4__ {int total_bytes; int unprocessed_bytes; } ;
struct TYPE_3__ {int total_bytes; int unprocessed_bytes; } ;
struct connection {int fd; int remote_port; int flags; int status; int error; int generation; int skip_bytes; int basic_type; int pending_queries; int ready; int parse_state; double last_response_time; double last_query_sent_time; double last_query_time; TYPE_2__ Out; TYPE_1__ In; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct sqlc_data* SQLC_DATA (struct connection*) ; 
 char* show_ip (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int,double,double,double) ; 

int dump_outbound_connection (struct connection *c, char *buff, int max_len) {
  struct sqlc_data *D = SQLC_DATA(c);
  return snprintf (buff, max_len,
                         "fd = %d, %s:%d, flags = %d , status = %d, err = %d, gen = %d, skip = %d, basic_type = %d\n"
                         "  Inb = %d + %d, Outb = %d + %d, pend = %d, ready = %d, parse_state=%d, type = %p\n"
                         "  auth state = %d, packet_state = %d\n"
                         "  last_response_time = %.6f, last_query_sent_time = %.6f, last_query_time = %.6f\n",
                         c->fd, show_ip (c->remote_ip), c->remote_port, c->flags, c->status, c->error, c->generation, c->skip_bytes, c->basic_type,
                         c->In.total_bytes, c->In.unprocessed_bytes, c->Out.total_bytes, c->Out.unprocessed_bytes,
                         c->pending_queries, c->ready, c->parse_state, c->type, 
                         D->auth_state, D->response_state,
                         c->last_response_time, c->last_query_sent_time, c->last_query_time);

}