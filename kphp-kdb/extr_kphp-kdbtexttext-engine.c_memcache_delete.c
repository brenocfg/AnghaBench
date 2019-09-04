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
 int do_delete_first_messages (int,int) ; 
 int do_delete_message (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free_tmp_buffers (struct connection*) ; 
 int set_user_secret (int,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 scalar_t__ unload_user_metafile (int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *key, int key_len) {
  int user_id, local_id;
  if (verbosity > 1) {
    fprintf (stderr, "memcache_delete: key='%s'\n", key);
  }

  free_tmp_buffers (c);

  if (key_len >= 8 && !strncmp (key, "userdata", 8)) {
    if (sscanf (key, "userdata%d", &user_id) == 1) {
      if (unload_user_metafile (user_id) > 0) {
 	write_out (&c->Out, "DELETED\r\n", 9);
	return 0;
      } else {
 	write_out (&c->Out, "NOT_FOUND\r\n", 11);
	return 0;
      }
    }
  }

  if (sscanf (key, "message%d_%d", &user_id, &local_id) == 2 && user_id && local_id > 0) {
    if (do_delete_message (user_id, local_id) == 1) {
      write_out (&c->Out, "DELETED\r\n", 9);
      return 0;
    } else {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
      return 0;
    }
  }

  if (sscanf (key, "first_messages%d_%d", &user_id, &local_id) == 2 && user_id && local_id > 0) {
    if (do_delete_first_messages (user_id, local_id) == 1) {
      write_out (&c->Out, "DELETED\r\n", 9);
      return 0;
    } else {
      write_out (&c->Out, "NOT_FOUND\r\n", 11);
      return 0;
    }
  }

  if (sscanf (key, "secret%d", &user_id) == 1 && user_id) { 
    if (set_user_secret (user_id, 0) == 1) {
      write_out (&c->Out, "DELETED\r\n", 9);
      return 0;
    }
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  return 0;
}