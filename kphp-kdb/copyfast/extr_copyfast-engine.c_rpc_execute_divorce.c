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
struct rpc_divorce {int dummy; } ;
struct relative {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  divorce_received; } ;
struct TYPE_4__ {TYPE_1__ structured; } ;

/* Variables and functions */
 TYPE_2__* STATS ; 
 int /*<<< orphan*/  delete_relative (struct relative*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct relative* get_relative_by_connection (struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_divorce (struct connection *c, struct rpc_divorce *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_divorce: len = %d\n", len);
  }
  if (len != sizeof (struct rpc_divorce)) {
    return 0;
  }
  STATS->structured.divorce_received ++;
  struct relative *x = get_relative_by_connection (c);
  if (x) {
    delete_relative (x, 0);
  }
  return 0;
}