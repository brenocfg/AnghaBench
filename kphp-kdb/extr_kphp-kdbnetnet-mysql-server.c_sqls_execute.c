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
struct connection {int dummy; } ;

/* Variables and functions */
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  send_error_packet (struct connection*,int,int,char*,int,int) ; 
 int sqls_builtin_execute (struct connection*,int) ; 

int sqls_execute (struct connection *c, int op) {
  int res = sqls_builtin_execute (c, op);
  if (res == SKIP_ALL_BYTES) {
    send_error_packet (c, 1045, 28000, "Failed", 6, 1);
  }
  return res;
}