#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpcs_data {unsigned int packet_len; int crypto_flags; int flags; int in_packet_num; unsigned int packet_num; unsigned int packet_crc32; scalar_t__ packet_type; } ;
struct TYPE_6__ {int total_bytes; } ;
struct connection {scalar_t__ status; int fd; int error; TYPE_2__ In; int /*<<< orphan*/  Q; scalar_t__ pending_queries; TYPE_1__* type; int /*<<< orphan*/  extra; int /*<<< orphan*/  custom_data; } ;
struct TYPE_7__ {int max_packet_len; int (* rpc_ready ) (struct connection*) ;int (* execute ) (struct connection*,scalar_t__,int) ;int /*<<< orphan*/  http_fallback_extra; TYPE_1__* http_fallback_type; int /*<<< orphan*/  memcache_fallback_extra; TYPE_1__* memcache_fallback_type; } ;
struct TYPE_5__ {scalar_t__ (* init_accepted ) (struct connection*) ;int (* parse_execute ) (struct connection*) ;} ;

/* Variables and functions */
 struct rpcs_data* RPCS_DATA (struct connection*) ; 
 TYPE_4__* RPCS_FUNC (struct connection*) ; 
 scalar_t__ RPC_PING ; 
 int SKIP_ALL_BYTES ; 
 int advance_skip_read_ptr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_expect_query ; 
 void* conn_reading_query ; 
 scalar_t__ conn_running ; 
 scalar_t__ conn_wait_aio ; 
 scalar_t__ conn_wait_net ; 
 unsigned int crc32_partial (char*,int,unsigned int) ; 
 int /*<<< orphan*/  dump_next_packet (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nbit_advance (int /*<<< orphan*/ *,int) ; 
 char* nbit_get_ptr (int /*<<< orphan*/ *) ; 
 int nbit_read_in (int /*<<< orphan*/ *,unsigned int*,int) ; 
 int nbit_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int nbit_total_ready_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_disable_crc32_check ; 
 int rpcs_default_execute (struct connection*,scalar_t__,int) ; 
 int rpcs_process_handshake_packet (struct connection*) ; 
 int rpcs_process_nonce_packet (struct connection*) ; 
 int rpcs_send_handshake_packet (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (struct connection*) ; 
 int stub2 (struct connection*) ; 
 scalar_t__ stub3 (struct connection*) ; 
 int stub4 (struct connection*) ; 
 int stub5 (struct connection*) ; 
 int stub6 (struct connection*,scalar_t__,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

int rpcs_parse_execute (struct connection *c) {
  struct rpcs_data *D = RPCS_DATA(c);
  int len;

  while (1) {
    len = nbit_total_ready_bytes (&c->Q);
    if (len <= 0) {
      break;
    }
    // fprintf (stderr, "in while : packet_len=%d, total_ready_bytes=%d; cptr=%p; c->status=%d\n", D->packet_len, len, c->Q.cptr, c->status);
    if (!D->packet_len) {
      if (len < 4) {
        c->status = conn_reading_query;
        return 4 - len;
      }
      assert (nbit_read_in (&c->Q, &D->packet_len, 4) == 4);
      // fprintf (stderr, "reading packet len [ = %d]\n", D->packet_len);
      len -= 4;
      if (D->crypto_flags & 512) {
	D->flags = (D->flags & 0x7fffffff) | (D->packet_len & 0x80000000);
	D->packet_len &= 0x7fffffff;
      }
      if (D->packet_len <= 0 || (D->packet_len & 0xc0000003)) {
        if (D->in_packet_num <= -2 && (D->packet_len == 0x656c6564 || D->packet_len == 0x74617473 || D->packet_len == 0x73726576 || D->packet_len == 0x20746567 || D->packet_len == 0x20746573 || D->packet_len == 0x20646461
                                                                   || D->packet_len == 0x6c706572 || D->packet_len == 0x72636e69 || D->packet_len == 0x72636564) && RPCS_FUNC(c)->memcache_fallback_type) {
	  vkprintf (1, "switching to memcache fallback for connection %d\n", c->fd);
          memset (c->custom_data, 0, sizeof (c->custom_data));
          c->type = RPCS_FUNC(c)->memcache_fallback_type;
          c->extra = RPCS_FUNC(c)->memcache_fallback_extra;
          if (c->type->init_accepted (c) < 0) {
	    vkprintf (1, "memcache init_accepted() returns error for connection %d\n", c->fd);
            c->status = conn_error;
            c->error = -33;
            return 0;
          }
          nbit_set (&c->Q, &c->In);
          return c->type->parse_execute (c);
        }
        if (D->in_packet_num <= -2 && (D->packet_len == 0x44414548 || D->packet_len == 0x54534f50 || D->packet_len == 0x20544547) && RPCS_FUNC(c)->http_fallback_type) {
	  vkprintf (1, "switching to http fallback for connection %d\n", c->fd);
          memset (c->custom_data, 0, sizeof (c->custom_data));
          c->type = RPCS_FUNC(c)->http_fallback_type;
          c->extra = RPCS_FUNC(c)->http_fallback_extra;
          if (c->type->init_accepted (c) < 0) {
	    vkprintf (1, "http init_accepted() returns error for connection %d\n", c->fd);
            c->status = conn_error;
            c->error = -33;
            return 0;
          }
          nbit_set (&c->Q, &c->In);
          return c->type->parse_execute (c);
        }
	vkprintf (1, "error while parsing packet: bad packet length %d\n", D->packet_len);
        c->status = conn_error;
        c->error = -1;
        return 0;
      }
      if (D->packet_len > RPCS_FUNC(c)->max_packet_len && RPCS_FUNC(c)->max_packet_len > 0) {
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
      //fprintf (stderr, "need %d bytes, only %d present; need %d more\n", D->packet_len, len + 4, D->packet_len - len - 4);
      c->status = conn_reading_query;
      return D->packet_len - len - 4;
    }
    assert (nbit_read_in (&c->Q, &D->packet_num, 8) == 8);
    unsigned crc32 = 0;
    if (!rpc_disable_crc32_check) {
      crc32 = crc32_partial (&D->packet_len, 12, -1);
      if ((D->flags < 0) && (D->crypto_flags & 512)) {
	crc32 ^= 0x1d80c620 ^ 0x7bd5c66f;
      }
    }

    //fprintf (stderr, "num = %d, len = %d\n", D->packet_num, D->packet_len);

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
    //fprintf (stderr, "check : crc32 = %08x ?= %08x\n", ~crc32, D->packet_crc32);
    if (~crc32 != D->packet_crc32 && !rpc_disable_crc32_check) {
      if (verbosity > 0) {
        dump_next_packet (c);
        fprintf (stderr, "error while parsing packet: crc32 = %08x != %08x\n", ~crc32, D->packet_crc32);
      }
      c->status = conn_error;
      c->error = -1;
      return 0;
    }

    if (verbosity > 2) {
      fprintf (stderr, "received packet from connection %d\n", c->fd);
      dump_next_packet (c);
    }

    int keep_total_bytes = c->In.total_bytes;
    int res = -1;

    if (D->in_packet_num == -3) {
      D->in_packet_num = 0;
    }

    if (!(D->crypto_flags & 256) && D->packet_num != D->in_packet_num) {
      vkprintf (1, "error while parsing packet: got packet num %d, expected %d\n", D->packet_num, D->in_packet_num);
      c->status = conn_error;
      c->error = -1;
      return 0;
    } else if (D->packet_num < 0) {
      /* this is for us */
      if (D->packet_num == -2) {
        c->status = conn_running;
        res = rpcs_process_nonce_packet (c);  // if res > 0, nonce packet sent in response
      } else if (D->packet_num == -1) {
        c->status = conn_running;
        res = rpcs_process_handshake_packet (c);
        if (res >= 0) {
          res = rpcs_send_handshake_packet (c);
          if (res >= 0 && RPCS_FUNC(c)->rpc_ready) {
            res = RPCS_FUNC(c)->rpc_ready (c);
          }
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
        res = rpcs_default_execute (c, D->packet_type, D->packet_len);
      } else {
        res = RPCS_FUNC(c)->execute (c, D->packet_type, D->packet_len);
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

    if (c->status == conn_running) {
      c->status = conn_expect_query;
    }

    //assert ((c->pending_queries && (c->status == conn_wait_net || c->status == conn_wait_aio)) || (!c->pending_queries && c->status == conn_expect_query));
    assert (c->status == conn_wait_net || (c->pending_queries && c->status == conn_wait_aio) || (!c->pending_queries && c->status == conn_expect_query));

    D->packet_len = 0;
    if (c->status != conn_expect_query) {
      break;
    }
    nbit_set (&c->Q, &c->In);
  }
  return 0;
}