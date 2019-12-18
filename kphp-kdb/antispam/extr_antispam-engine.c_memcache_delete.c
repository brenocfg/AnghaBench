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
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_pattern ; 
 scalar_t__ do_del_pattern (int) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int const) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  INIT;

  // delete ("pattern{$id}");
  const int shift = 7; // shift == |pattern|
  if (key_len >= shift && !strncmp (key, "pattern", shift)) {
    int id = 0, already_read = 0;
    if (sscanf (key + shift, "%d%n", &id, &already_read) >= 1 && !key[shift + already_read]) {
      if (do_del_pattern (id)) {
        write_out (&c->Out, "DELETED\r\n", 9);
        RETURN (del_pattern, 0);
      }
    }
  }
  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  RETURN (del_pattern, 0);
}