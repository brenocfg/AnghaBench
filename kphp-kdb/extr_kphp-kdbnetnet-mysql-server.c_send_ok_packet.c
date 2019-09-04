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
struct connection {int /*<<< orphan*/  flags; int /*<<< orphan*/  Out; } ;
typedef  int /*<<< orphan*/  nbw_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_WANTWR ; 
 int /*<<< orphan*/  nbit_setw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_write_out (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  sqls_flush_packet (struct connection*,int) ; 
 scalar_t__ write_lcb (struct connection*,unsigned long long) ; 
 scalar_t__ write_out (int /*<<< orphan*/ *,...) ; 

int send_ok_packet (struct connection *c, unsigned long long affected_rows,
                    unsigned long long insert_id, int server_status, 
                    int warning_count, const char *message, int msg_len,
                    int sequence_number) {
  nbw_iterator_t it;

  int res = 0;

  nbit_setw (&it, &c->Out);
  sequence_number <<= 24;
  write_out (&c->Out, &sequence_number, 4);

  res += write_out (&c->Out, "", 1);
  res += write_lcb (c, affected_rows);
  res += write_lcb (c, insert_id);
  res += write_out (&c->Out, &server_status, 2);
  res += write_out (&c->Out, &warning_count, 2);
  res += write_out (&c->Out, message, msg_len);
  
  nbit_write_out (&it, &res, 3);

  sqls_flush_packet (c, res);
  c->flags |= C_WANTWR;
  
  return res + 4;
}