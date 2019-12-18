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
 int /*<<< orphan*/  assert (int) ; 
 int sprintf (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int return_one_key (struct connection *c, const char *key, char *val, int vlen) {
  static char buff[65536];
  int l = sprintf (buff, "VALUE %s 0 %d\r\n", key, vlen);
  assert (l <= 65536);
  write_out (&c->Out, buff, l);
  write_out (&c->Out, val, vlen);
  write_out (&c->Out, "\r\n", 2);
  return 0;
}