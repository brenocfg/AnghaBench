#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int /*<<< orphan*/  Out; } ;
struct TYPE_3__ {int data_len; char* data; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_OPER (int) ; 
 int /*<<< orphan*/  add_entry_used (int) ; 
 int /*<<< orphan*/  cmd_decr ; 
 int /*<<< orphan*/  cmd_incr ; 
 int /*<<< orphan*/  del_entry_used (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,long long) ; 
 int get_entry (char const*,int,long long) ; 
 TYPE_1__* get_entry_ptr (int) ; 
 long long get_hash (char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zzfree (unsigned long long*,int) ; 
 char* zzmalloc (int) ; 

int memcache_incr (struct connection *c, int op, const char *key, int key_len, long long arg) {
  if (verbosity > 0) {
    fprintf (stderr, "memcache_incr: op=%d, key='%s', val=%lld\n", op, key, arg);
  }
  if (arg < 0) {
    arg *= -1;
    op ^= 1;
  }

  if (op == 1) {
    cmd_decr++;
  } else {
    cmd_incr++;
  }

  long long key_hash = get_hash (key, key_len);
  int x = get_entry (key, key_len, key_hash);

  ADD_OPER (2);

  if (x == -1) {
    write_out (&c->Out, "NOT_FOUND\r\n", 11);
    return 0;
  }

  hash_entry_t *entry = get_entry_ptr (x);

  unsigned long long val = 0;
  int i, f = 1;

  for (i = 0; i < entry->data_len && f; i++) {
    if ('0' <= entry->data[i] && entry->data[i] <= '9') {
      val = val * 10 + entry->data[i] - '0';
    } else {
      f = 0;
    }
  }

  if (f == 0) {
    val = 0;
  }

  if (op == 1) {
    if ((unsigned long long)arg > val) {
      val = 0;
    } else {
      val -= arg;
    }
  } else {
    val += (unsigned long long)arg;
  }

  zzfree (entry->data, entry->data_len + 1);
  del_entry_used (x);
  add_entry_used (x);

  char buff[30];
  sprintf (buff, "%llu", val);

  int len = strlen (buff);

  char *d = zzmalloc (len + 1);
  memcpy (d, buff, len + 1);

  entry->data = d;
  entry->data_len = len;

  write_out (&c->Out, d, len);
  write_out (&c->Out, "\r\n", 2);

  return 0;
}