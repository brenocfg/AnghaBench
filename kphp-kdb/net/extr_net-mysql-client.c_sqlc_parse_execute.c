#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sqlc_data {int packet_state; int packet_len; unsigned int packet_seq; int block_size; int packet_padding; scalar_t__ auth_state; int crypto_flags; } ;
struct TYPE_6__ {int total_bytes; } ;
struct connection {int fd; int status; int flags; int error; int remote_port; int /*<<< orphan*/  Q; TYPE_1__ In; int /*<<< orphan*/  remote_ip; int /*<<< orphan*/  last_response_time; } ;
struct TYPE_7__ {int (* execute ) (struct connection*,int) ;int /*<<< orphan*/  (* sql_becomes_ready ) (struct connection*) ;scalar_t__ (* sql_authorized ) (struct connection*) ;} ;

/* Variables and functions */
 int C_FAILED ; 
 int C_STOPREAD ; 
 int SKIP_ALL_BYTES ; 
 struct sqlc_data* SQLC_DATA (struct connection*) ; 
 TYPE_5__* SQLC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  advance_skip_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* conn_error ; 
 int conn_reading_answer ; 
 int conn_ready ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_answer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_read_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_all_unprocessed (TYPE_1__*) ; 
 scalar_t__ nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int nbit_total_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  precise_now ; 
 char* show_ip (int /*<<< orphan*/ ) ; 
 scalar_t__ sql_auth_initdb ; 
 scalar_t__ sql_auth_ok ; 
 scalar_t__ sql_auth_sent ; 
 scalar_t__ sql_noauth ; 
 int sqlc_inner_authorise (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (struct connection*) ; 
 int /*<<< orphan*/  stub2 (struct connection*) ; 
 int stub3 (struct connection*,int) ; 
 int verbosity ; 

int sqlc_parse_execute (struct connection *c) {
  struct sqlc_data *D = SQLC_DATA(c);
  int len = nbit_total_ready_bytes (&c->Q);
  static unsigned int psize;
  if (verbosity > 1) {
    fprintf (stderr, "sqlc_parse_execute(%d), status=%d, bytes=%d, packet_state=%d, packet_len=%d\n", c->fd, c->status, len, D->packet_state, D->packet_len);
  }
  char *p;

  while (len > 0 && !(c->flags & (C_FAILED | C_STOPREAD))) {
    c->status = conn_reading_answer;
    if (D->packet_state == 0) {
      if (len < 4) {
        return 4 - len;
      }
      assert (nbit_read_in (&c->Q, &psize, 4) == 4);
      len -= 4;
      D->packet_state = 1;
      D->packet_len = psize & 0xffffff;
      D->packet_seq = (psize >> 24);
      if (D->block_size > 1) {
        D->packet_padding = D->block_size - (D->packet_len + 4) % D->block_size;
        if (D->packet_padding == D->block_size) {
          D->packet_padding = 0;
        }
      }
    }
    assert (D->packet_state == 1);
    if (len < D->packet_len + D->packet_padding) {
      return D->packet_len + D->packet_padding - len;
    }
    /* complete packet ready */
    c->last_response_time = precise_now;
    if (verbosity > 1) {
      fprintf (stderr, "client packet ready: len=%d, seq_num=%d\n", D->packet_len, D->packet_seq);
    }
    if (D->auth_state == sql_noauth) {
      int res = sqlc_inner_authorise(c);
      if (res < 0) {
        c->status = conn_error;
        c->error = -1;
        return 0;
      }
      D->auth_state = sql_auth_sent;
      advance_skip_read_ptr (&c->In, D->packet_len + D->packet_padding + 4);
      if ((D->crypto_flags & 10) == 10) {
        mark_all_unprocessed (&c->In);
      }
      nbit_set (&c->Q, &c->In);
      len = nbit_ready_bytes (&c->Q);
    } else 
    if (D->auth_state == sql_auth_sent) {
      /* parse OK|failed */
      p = ((char *)get_read_ptr (&c->In)) + 4;
      if (D->packet_len == 0 || *p) {
        c->status = conn_error;
        c->error = -1;
        fprintf (stderr, "ok packet expected in response to authentification from connection %d (%s:%d)\n", c->fd, show_ip (c->remote_ip), c->remote_port);
        return 0;
      }
      D->auth_state = sql_auth_ok;
      advance_skip_read_ptr (&c->In, D->packet_len + D->packet_padding + 4);

      if (SQLC_FUNC(c)->sql_authorized (c)) {
        c->status = conn_error;
        c->error = -1;
        if (verbosity > 1) {
          fprintf (stderr, "sql authorisation failed\n");
        }
        return 0;
      }

      if (verbosity > 1) {
        fprintf (stderr, "outcoming authorization successful\n");
      }

    } else 
    if (D->auth_state == sql_auth_initdb) {
      p = ((char *)get_read_ptr (&c->In)) + 4;
      if (D->packet_len == 0 || *p) {
        c->status = conn_error;
        c->error = -1;
        if (verbosity > 1) {
          fprintf (stderr, "ok packet expected in response to initdb\n");
        }
        return 0;
      }
      D->auth_state = sql_auth_ok;
      advance_skip_read_ptr (&c->In, D->packet_len + D->packet_padding + 4);
      c->status = conn_ready;
      D->packet_state = 0;
      /*if (SQLC_FUNC(c)->sql_authorized (c)) {
        c->status = conn_error;
        c->error = -1;
        fprintf (stderr, "ok packet expected\n");
        return 0;
      }*/
      if (verbosity > 1) {
        fprintf (stderr, "outcoming initdb successful\n");
      }
      SQLC_FUNC(c)->sql_becomes_ready (c);
      return 0;
    } else {
      int op = (D->packet_len > 0 ? *(char *) nbit_get_ptr (&c->Q) : -1);

      assert (D->auth_state == sql_auth_ok);

      //dump_connection_buffers (c);
      if (verbosity > 1) {
        fprintf (stderr, "execute, op=%d\n", op);
      }

      int keep_total_bytes = c->In.total_bytes;

      /* execute */
      c->status = conn_running;
      int res = SQLC_FUNC(c)->execute (c, op);

      //dump_connection_buffers (c);

      if (res == SKIP_ALL_BYTES) {
//      assert (keep_total_bytes == c->In.total_bytes);  // this assert FAILS!
        if (keep_total_bytes != c->In.total_bytes) {
          fprintf (stderr, "error: in SKIP_ALL_BYTES for connection %d: keep_total=%d != total_bytes=%d, packet_len=%d, packet_padding=%d, packet_state=%d, packet_seq=%d, op=%d, status=%d\n", 
          		    c->fd, keep_total_bytes, c->In.total_bytes, D->packet_len, D->packet_padding, D->packet_state, D->packet_seq, op, c->status);
        }
        advance_skip_read_ptr (&c->In, D->packet_len + D->packet_padding + 4);
      } else if (keep_total_bytes != c->In.total_bytes) {
        assert (keep_total_bytes == c->In.total_bytes + D->packet_len + 4);
        advance_skip_read_ptr (&c->In, D->packet_padding);
      }
    }
    nbit_set (&c->Q, &c->In);
    len = nbit_ready_bytes (&c->Q);
    D->packet_state = 0;
    if (c->status == conn_running) {
      c->status = conn_wait_answer;
    }
  }

  return 0;
}