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
struct nb_iterator {int dummy; } ;
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int nbit_read_in (struct nb_iterator*,int*,int) ; 
 int /*<<< orphan*/  nbit_set (struct nb_iterator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void dump_next_rpc_packet_limit (struct connection *c, int max_ints) {
  struct nb_iterator it;
  int i = 0, len = 4, x;
  nbit_set (&it, &c->In);
  while (i * 4 < len && i < max_ints) {
    assert (nbit_read_in (&it, &x, 4) == 4);
    if (!i) {
      len = x;
    }
    fprintf (stderr, "%08x ", x);
    if (!(++i & 7)) {
      fprintf (stderr, "\n");
    }
  }
  fprintf (stderr, "\n");
}