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
struct rpcs_data {int crypto_flags; int packet_len; int in_packet_num; int flags; int packet_type; int packet_num; } ;
struct TYPE_4__ {int total_bytes; } ;
struct connection {scalar_t__ status; int error; TYPE_1__ In; int /*<<< orphan*/  Q; int /*<<< orphan*/  pending_queries; } ;
struct TYPE_5__ {int max_packet_len; int (* execute ) (struct connection*,int,int) ;} ;

/* Variables and functions */
 struct rpcs_data* RPCS_DATA (struct connection*) ; 
 TYPE_3__* RPCS_FUNC (struct connection*) ; 
 int SKIP_ALL_BYTES ; 
 int advance_skip_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conn_error ; 
 scalar_t__ conn_expect_query ; 
 void* conn_reading_query ; 
 scalar_t__ conn_running ; 
 int nbit_read_in (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  nbit_set (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int nbit_total_ready_bytes (int /*<<< orphan*/ *) ; 
 int rpcs_parse_execute (struct connection*) ; 
 int stub1 (struct connection*,int,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rpcs_compact_parse_execute (struct connection *c) {
  struct rpcs_data *D = RPCS_DATA(c);
  int len;

  if (D->crypto_flags & 1024) {
    return rpcs_parse_execute (c);
  }

  while (1) {
    len = nbit_total_ready_bytes (&c->Q);
    if (len <= 0) {
      break;
    }
    if (!D->packet_len) {
      if (len < 5) {
        c->status = conn_reading_query;
        return 5 - len;
      }
      assert (nbit_read_in (&c->Q, &D->packet_len, 1) == 1);
      len--;
      if (D->in_packet_num == -3) {
	if (D->packet_len != 0xef) {
	  D->crypto_flags |= 1024;
	  nbit_set (&c->Q, &c->In);
	  D->packet_len = 0;
	  return rpcs_parse_execute (c);
	}
	D->in_packet_num = 0;
	D->flags |= 0x40000000;
	assert (advance_skip_read_ptr (&c->In, 1) == 1);
	assert (nbit_read_in (&c->Q, &D->packet_len, 1) == 1);
	len--;
      }
      if (D->packet_len & 0x80) {
	D->flags |= 0x80000000;
	D->packet_len &= 0x7f;
      } else {
	D->flags &= 0x7fffffff;
      }
      if (D->packet_len == 0x7f) {
	assert (nbit_read_in (&c->Q, &D->packet_len, 3) == 3);
	if (D->packet_len < 0x7f) {
	  vkprintf (1, "error while parsing compact packet: got length %d in overlong encoding\n", D->packet_len);
	  c->status = conn_error;
	  c->error = -1;
	  return 0;
	}
	len -= 3;
      } else if (!D->packet_len) {
	vkprintf (1, "error while parsing compact packet: got zero packet length\n");
	c->status = conn_error;
	c->error = -1;
	return 0;
      }
      D->packet_len <<= 2;
      if (D->packet_len > RPCS_FUNC(c)->max_packet_len && RPCS_FUNC(c)->max_packet_len > 0) {
	vkprintf (1, "error while parsing packet: bad packet length %d\n", D->packet_len);
	c->status = conn_error;
	c->error = -1;
	return 0;
      }
    }
    if (len < D->packet_len) {
      c->status = conn_reading_query;
      return D->packet_len - len;
    }
    assert (nbit_read_in (&c->Q, &D->packet_type, 4) == 4);

    if (D->packet_len <= 0x7e * 4) {
      assert (advance_skip_read_ptr (&c->In, 1) == 1);
    } else {
      assert (advance_skip_read_ptr (&c->In, 4) == 4);
    }
    D->packet_num = D->in_packet_num;
    
    int keep_total_bytes = c->In.total_bytes;
    int res;

    /* main case */
    c->status = conn_running;
    res = RPCS_FUNC(c)->execute (c, D->packet_type, D->packet_len);

    if (c->status == conn_error) {
      if (!c->error) {
        c->error = -2;
      }
      return 0;
    }

    if (res == SKIP_ALL_BYTES) {
      assert (keep_total_bytes == c->In.total_bytes);
      advance_skip_read_ptr (&c->In, D->packet_len);
    } else {
      assert (keep_total_bytes == c->In.total_bytes + D->packet_len);
    }
    D->in_packet_num++;

    assert (!c->pending_queries && c->status == conn_running);
    c->status = conn_expect_query;

    D->packet_len = 0;
    nbit_set (&c->Q, &c->In);
  }
  return 0;
}