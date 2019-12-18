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
 scalar_t__ delete_temp_transaction (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  int temp_id;
  if (verbosity > 1) {
    fprintf (stderr, "memcache_delete: key='%s'\n", key);
  }

  if (sscanf (key, "transaction%d", &temp_id) >= 1 && temp_id > 0) {
    if (delete_temp_transaction (temp_id) > 0) {
      write_out (&c->Out, "DELETED\r\n", 9);
      return 0;
    } else {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
      return 0;
    }
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}