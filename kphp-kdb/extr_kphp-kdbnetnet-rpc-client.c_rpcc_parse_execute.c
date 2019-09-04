#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpcc_data {unsigned int packet_len; unsigned int packet_num; unsigned int packet_crc32; unsigned int in_packet_num; scalar_t__ packet_type; } ;
struct TYPE_4__ {int total_bytes; } ;
struct connection {scalar_t__ status; int error; int fd; TYPE_1__ In; int /*<<< orphan*/  Q; } ;
struct TYPE_5__ {int max_packet_len; int (* rpc_ready ) (struct connection*) ;int (* execute ) (struct connection*,scalar_t__,int) ;} ;

/* Variables and functions */
 struct rpcc_data* RPCC_DATA (struct connection*) ; 
 TYPE_3__* RPCC_FUNC (struct connection*) ; 
 scalar_t__ RPC_PING ; 
 int SKIP_ALL_BYTES ; 
 int advance_skip_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_error ; 
 void* conn_reading_answer ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_answer ; 
 unsigned int crc32_partial (char*,int,unsigned int) ; 
 int /*<<< orphan*/  dump_next_rpc_packet (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int nbit_advance (int /*<<< orphan*/ *,int) ; 
 char* nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int nbit_total_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_disable_crc32_check ; 
 int rpcc_default_execute (struct connection*,scalar_t__,int) ; 
 int rpcc_process_handshake_packet (struct connection*) ; 
 int rpcc_process_nonce_packet (struct connection*) ; 
 int rpcc_send_handshake_packet (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (struct connection*) ; 
 int stub2 (struct connection*,scalar_t__,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,unsigned int,...) ; 

int rpcc_parse_execute (struct connection *c) {
  struct rpcc_data *D = RPCC_DATA(c);
  int len;

  while (1) {
    len = nbit_total_ready_bytes (&c->Q);
    if (len <= 0) {
      break;
    }
    if (!D->packet_len) {
      if (len < 4) {
        c->status = conn_reading_answer;
        return 4 - len;
      }
      assert (nbit_read_in (&c->Q, &D->packet_len, 4) == 4);
      len -= 4;
      if (D->packet_len <= 0 || (D->packet_len & 3) || (D->packet_len > RPCC_FUNC(c)->max_packet_len && RPCC_FUNC(c)->max_packet_len > 0)) {
	vkprintf (1, "error while parsing packet: bad packet length %d\n", D->packet_len);
        c->status = conn_error;
        c->error = -1;
        return 0;
      }
    }
    if (D->packet_len == 4) {
      assert (advance_skip_read_ptr (&c->In, 4) == 4);
      D->packet_len = 0;
      nbit_set (&c->Q, &c->In);
      continue;
    }
    if (D->packet_len < 16) {
      vkprintf (1, "error while parsing packet: bad packet length %d\n", D->packet_len);
      c->status = conn_error;
      c->error = -1;
      return 0;
    }
    if (len + 4 < D->packet_len) {
      c->status = conn_reading_answer;
      return D->packet_len - len - 4;
    }
    assert (nbit_read_in (&c->Q, &D->packet_num, 8) == 8);    
    unsigned crc32 = !rpc_disable_crc32_check ? crc32_partial (&D->packet_len, 12, -1) : 0;
    len = D->packet_len - 16;
    while (len > 0) {
      int l = nbit_ready_bytes (&c->Q);
      char *ptr = nbit_get_ptr (&c->Q);
      if (l > len) {
        l = len;
      }
      assert (l > 0);
      if (!rpc_disable_crc32_check) {
        crc32 = crc32_partial (ptr, l, crc32);
      }
      len -= l;
      assert (nbit_advance (&c->Q, l) == l);
    }
    assert (!len);
    assert (nbit_read_in (&c->Q, &D->packet_crc32, 4) == 4);
    if (~crc32 != D->packet_crc32 && !rpc_disable_crc32_check) {
      vkprintf (1, "error while parsing packet: crc32 = %08x != %08x\n", ~crc32, D->packet_crc32);
      c->status = conn_error;
      c->error = -1;
      return 0;
    }

    if (verbosity > 2) {
      fprintf (stderr, "received packet from connection %d\n", c->fd);
      dump_next_rpc_packet (c);
    }

    int keep_total_bytes = c->In.total_bytes;
    int res = -1;

    if (D->packet_num != D->in_packet_num) {
      vkprintf (1, "error while parsing packet: got packet num %d, expected %d\n", D->packet_num, D->in_packet_num);
      c->status = conn_error;
      c->error = -1;
      return 0;
    } else if (D->packet_num < 0) {
      /* this is for us */
      if (D->packet_num == -2) {
        c->status = conn_running;
        res = rpcc_process_nonce_packet (c);
        if (res >= 0) {
          res = rpcc_send_handshake_packet (c);
          //fprintf (stderr, "send_handshake_packet returned %d\n", res);
        }
      } else if (D->packet_num == -1) {
        c->status = conn_running;
        res = rpcc_process_handshake_packet (c);
        if (res >= 0 && RPCC_FUNC(c)->rpc_ready) {
          res = RPCC_FUNC(c)->rpc_ready (c);
        }
      }
      if (res < 0) {
        c->status = conn_error;
        c->error = res;
        return 0;
      }
    } else {
      /* main case */
      c->status = conn_running;
      if (D->packet_type == RPC_PING) {
        res = rpcc_default_execute (c, D->packet_type, D->packet_len);
      } else {
        res = RPCC_FUNC(c)->execute (c, D->packet_type, D->packet_len);
      }
    }

    if (c->status == conn_error) {
      if (!c->error) {
        c->error = -2;
      }
      return 0;
    }

    if (res == SKIP_ALL_BYTES) {
      assert (keep_total_bytes == c->In.total_bytes);
      advance_skip_read_ptr (&c->In, D->packet_len);
      D->in_packet_num++;
    } else if (keep_total_bytes != c->In.total_bytes) {
      assert (keep_total_bytes == c->In.total_bytes + D->packet_len);
      D->in_packet_num++;
    }
    D->packet_len = 0;
    if (c->status == conn_running) {
      c->status = conn_wait_answer;
    }
    if (c->status != conn_wait_answer) {
      break;
    }
    nbit_set (&c->Q, &c->In);
  }
  return 0;
}