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
 int /*<<< orphan*/  cmd_global ; 
 int /*<<< orphan*/  delete ; 
 scalar_t__ do_del_object_text (int,long long) ; 
 scalar_t__ do_del_user_object (int,int,long long) ; 
 int /*<<< orphan*/  eat_at (char const*,int,char**,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  history_q_add (char*,int) ; 
 int sscanf (char*,char*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int memcache_delete (struct connection *c, const char *old_key, int old_key_len) {
  INIT;

  if (verbosity > 1) {
    fprintf (stderr, "memcache_delete: key='%s'\n", old_key);
  }

  char *key;
  int key_len;

  eat_at (old_key, old_key_len, &key, &key_len);

  history_q_add (key, 3);

  //Удаление объекта для одного пользователя
  //delete ("user_object{$user_id},{$type}:{$object_id}")
  if (key_len >= 11 && !strncmp (key, "user_object", 11)) {
    int user_id, type;
    long long object_id;
    int object_id2;

    int t = sscanf (key + 11, "%d,%d:%lld_%d", &user_id, &type, &object_id, &object_id2);
    if (t == 3 || t == 4) {
      if (t == 4) {
        if (object_id == user_id || object_id2 == user_id) {
          write_out (&c->Out, "NOT_FOUND\r\n", 11);
          RETURN(delete, 0);
        }
        if (object_id == user_id) {
          object_id = object_id2;
        }
      }
      if (do_del_user_object (user_id, type, object_id)) {
        write_out (&c->Out, "DELETED\r\n", 9);
      } else {
        write_out (&c->Out, "NOT_FOUND\r\n", 11);
      }
      RETURN(delete, 0);
    }

    write_out (&c->Out, "NOT_FOUND\r\n", 11);
    RETURN(delete, 0);
  }

  //Удаление объекта
  //delete ("object_text{$type}:{$object_id}")
  if (key_len >= 11 && !strncmp (key, "object_text", 11)) {
    int type;
    long long object_id;
    int object_id2;

    int t = sscanf (key + 11, "%d:%lld_%d", &type, &object_id, &object_id2);
    if (t == 2 || t == 3) {
      if (t == 3) {
        write_out (&c->Out, "NOT_FOUND\r\n", 11);
        RETURN(delete, 0);
      }

      if (do_del_object_text (type, object_id)) {
        write_out (&c->Out, "DELETED\r\n", 9);
      } else {
        write_out (&c->Out, "NOT_FOUND\r\n", 11);
      }
      cmd_global++;
      RETURN(delete, 0);
    }

    write_out (&c->Out, "NOT_FOUND\r\n", 11);
    RETURN(delete, 0);
  }

  write_out (&c->Out, "NOT_FOUND\r\n", 11);
  RETURN(delete, 0);
}