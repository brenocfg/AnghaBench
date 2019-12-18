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
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char const*,int) ; 

int return_one_key_false (struct connection *c, const char *key, int key_len) {
  write_out (&c->Out, "VALUE ", 6);
  write_out (&c->Out, key, key_len);
  write_out (&c->Out, " 1 4\r\nb:0;\r\n", 12);
  return 0;
}