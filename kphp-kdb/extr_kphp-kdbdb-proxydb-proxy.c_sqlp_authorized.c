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
struct connection {int /*<<< orphan*/  Out; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  nbw_iterator_t ;
struct TYPE_4__ {int /*<<< orphan*/  auth_state; scalar_t__ packet_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sql_flush_packet ) (struct connection*,int) ;int /*<<< orphan*/  (* sql_becomes_ready ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* SQLC_DATA (struct connection*) ; 
 TYPE_1__* SQLC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  conn_ready ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nbit_setw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbit_write_out (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  sql_auth_initdb ; 
 int /*<<< orphan*/  sql_auth_ok ; 
 char* sql_database ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int /*<<< orphan*/  stub2 (struct connection*,int) ; 
 int verbosity ; 
 scalar_t__ write_out (int /*<<< orphan*/ *,...) ; 

int sqlp_authorized (struct connection *c) {
  nbw_iterator_t it;
  unsigned temp = 0x00000000;
  int len = 0;
  char ptype = 2;

  if (!sql_database || !*sql_database) {
    SQLC_DATA(c)->auth_state = sql_auth_ok;
    c->status = conn_ready;
    SQLC_DATA(c)->packet_state = 0;
    if (verbosity > 1) {
      fprintf (stderr, "outcoming initdb successful\n");
    }
    SQLC_FUNC(c)->sql_becomes_ready (c);
    return 0;
  }

  nbit_setw (&it, &c->Out);
  write_out (&c->Out, &temp, 4);

  len += write_out (&c->Out, &ptype, 1);
  if (sql_database && *sql_database) {
    len += write_out (&c->Out, sql_database, strlen (sql_database));
  }

  nbit_write_out (&it, &len, 3);

  SQLC_FUNC(c)->sql_flush_packet (c, len);

  SQLC_DATA(c)->auth_state = sql_auth_initdb;
  return 0;
}