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
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int return_one_key_int (struct connection *c, const char *key, int i) {
  static char buff[256], s[32];
  int vlen = sprintf (s, "i:%d;", i);
  int l = sprintf (buff, "VALUE %s 1 %d\r\n", key, vlen);
  write_out (&c->Out, buff, l);
  write_out (&c->Out, s, vlen);
  write_out (&c->Out, "\r\n", 2);
  return 0;
}