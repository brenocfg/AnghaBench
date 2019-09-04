#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sqls_data {int packet_state; unsigned int packet_len; unsigned int output_packet_seq; unsigned int packet_seq; int block_size; int packet_padding; scalar_t__ auth_state; int crypto_flags; int auth_user; } ;
struct TYPE_7__ {int total_bytes; scalar_t__ pptr; } ;
struct connection {int fd; int flags; int status; int error; int /*<<< orphan*/  Q; TYPE_2__ In; TYPE_1__* type; scalar_t__ crypto; } ;
struct TYPE_8__ {int (* sql_start_crypto ) (struct connection*,char*,int) ;int (* execute ) (struct connection*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* crypto_decrypt_input ) (struct connection*) ;} ;

/* Variables and functions */
 int C_FAILED ; 
 int C_STOPREAD ; 
 int SKIP_ALL_BYTES ; 
 struct sqls_data* SQLS_DATA (struct connection*) ; 
 TYPE_5__* SQLS_FUNC (struct connection*) ; 
 int /*<<< orphan*/  advance_skip_read_ptr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* conn_error ; 
 scalar_t__ conn_expect_query ; 
 int conn_reading_query ; 
 int conn_running ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int nbit_total_ready_bytes (int /*<<< orphan*/ *) ; 
 int read_in (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  send_error_packet (struct connection*,int,int,char*,int,int) ; 
 int /*<<< orphan*/  send_ok_packet (struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ sql_auth_ok ; 
 scalar_t__ sql_auth_sent ; 
 int sqls_inner_authorise (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (struct connection*,char*,int) ; 
 int /*<<< orphan*/  stub2 (struct connection*) ; 
 int stub3 (struct connection*,int) ; 
 int verbosity ; 

int sqls_parse_execute (struct connection *c) {
  struct sqls_data *D = SQLS_DATA(c);
  int len = nbit_total_ready_bytes (&c->Q);
  static unsigned int psize;
  if (verbosity > 1) {
    fprintf (stderr, "sqls_parse_execute(%d), bytes=%d\n", c->fd, len);
  }

  while (len > 0 && !(c->flags & (C_FAILED | C_STOPREAD))) {
    c->status = conn_reading_query;
    if (D->packet_state == 0) {
      if (len < 4) {
        return 4 - len;
      }
      assert (nbit_read_in (&c->Q, &psize, 4) == 4);
      len -= 4;
      D->packet_state = 1;
      D->packet_len = psize & 0xffffff;
      D->output_packet_seq = D->packet_seq = (psize >> 24);
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
    if (verbosity > 1) {
      fprintf (stderr, "client packet ready: len=%d, padding=%d, seq_num=%d\n", D->packet_len, D->packet_padding, D->packet_seq);
    }
    if (D->auth_state == sql_auth_sent) {
      int res;
      if (D->packet_len == 16 && D->packet_seq == 0xcc && (D->crypto_flags & 14) == 6) {
        static char nonce_buff[20];
        assert (read_in (&c->In, nonce_buff, D->packet_len + 4) == 20);
        res = SQLS_FUNC(c)->sql_start_crypto (c, nonce_buff + 4, 16);
        if (res != 1) {
          res = -1;
        } else {
          D->crypto_flags = (D->crypto_flags & -16) | 10;
          assert (c->type->crypto_decrypt_input && c->crypto && c->In.pptr);
          c->type->crypto_decrypt_input (c);
          nbit_set (&c->Q, &c->In);
          len = nbit_total_ready_bytes (&c->Q);
          D->packet_state = 0;
          c->status = conn_expect_query;
          continue;
        }
      } else {
        if (D->crypto_flags & 4) {
          D->crypto_flags &= ~6;
          if (!(D->crypto_flags & 1)) {
            c->status = conn_error;
            c->error = -1;
            return 0;
          }
        }
        res = sqls_inner_authorise(c);
      }
      if (res < 0) {
        c->status = conn_error;
        c->error = -1;
        return 0;
      }
      if (res) {
        /* send ok packet */
        send_ok_packet (c, 0, 0, 2, 0, "Success", 7, 2);
        if (verbosity > 1) {
          fprintf (stderr, "authorized ok\n");
        }
        D->auth_state = sql_auth_ok;
        D->auth_user = res;
      } else {
        if (verbosity > 1) {
          fprintf (stderr, "authorization error\n");
        }
        send_error_packet (c, 1045, 28000, "Failed", 6, 2);
        /* send error packet */
      }
      advance_skip_read_ptr (&c->In, D->packet_len + D->packet_padding + 4);
    } else {
      int op = (D->packet_len > 0 ? *(char *) nbit_get_ptr (&c->Q) : -1);

      assert (D->auth_state == sql_auth_ok);

      if (verbosity > 1) {
        fprintf (stderr, "execute, op=%d\n", op);
      }

      int keep_total_bytes = c->In.total_bytes;

      /* execute */
      c->status = conn_running;
      int res = SQLS_FUNC(c)->execute (c, op);

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
      if (c->status == conn_running) {
        c->status = conn_expect_query;
      }
    }
    D->packet_state = 0;
    if (c->status != conn_expect_query) {
      break;
    }
    nbit_set (&c->Q, &c->In);
    len = nbit_total_ready_bytes (&c->Q);
  }

  return 0;
}