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
struct hints_gather_extra {int limit; scalar_t__ need_rating; } ;
struct gather_entry {scalar_t__ num; } ;
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 scalar_t__ HINTS_MERGE_EXTENSION ; 
 int Q_limit ; 
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_gather_heap (int /*<<< orphan*/ ) ; 
 int eat_at (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  gather_heap_advance () ; 
 int /*<<< orphan*/  gather_heap_insert (struct gather_entry*) ; 
 int* get_gather_heap_head () ; 
 char* get_write_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int return_one_key (struct connection*,char const*,char*,int) ; 
 size_t sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char const*,int) ; 

int hints_merge_end_query (struct connection *c, const char *key, int key_len, void *E, struct gather_entry *data, int tot_num) {
  struct hints_gather_extra *extra = E;
  assert (E != 0);
  static char buff[2048];
  int w, i;
  int res = 0;
  char *ptr, *size_ptr, *s;
  int len = key_len;

  Q_limit = extra->limit;

  int at_l = eat_at (key, len);
  key += at_l;
  len -= at_l;

  clear_gather_heap (0);
  for (i = 0; i < tot_num; i++) if (data[i].num >= 0) {
    res += data[i].num;
    assert (data[i].num >= 0);
    if (verbosity >= 4) {
      fprintf (stderr, "Using result %d (num = %d)\n", i, data[i].num);
    }
    gather_heap_insert (&data[i]);
  } else {
    if (verbosity >= 4) {
      fprintf (stderr, "Dropping result %d (num = %d)\n", i, data[i].num);
    }
  }

  if (verbosity > 0) {
    fprintf (stderr, "result = %d\n", res);
  }

  if (!Q_limit || !res) {
    w = sprintf (buff, "%d", res);
    return return_one_key (c, key, buff, w);
  }

  write_out (&c->Out, "VALUE ", 6);
  write_out (&c->Out, key, len);

  ptr = get_write_ptr (&c->Out, 512);
  if (!ptr) return -1;
  s = ptr + 448;

  memcpy (ptr, " 0 .........\r\n", 14);
  size_ptr = ptr + 3;
  ptr += 14;
  ptr += w = sprintf (ptr, "%d", res);
  
  //char split;
  //int id_bytes;
  if (HINTS_MERGE_EXTENSION) {
  } else {
    assert (0);
  }

  for (i = 0; i < Q_limit; ) {
    int t, *Res = get_gather_heap_head ();
    if (!Res) { break; }
    
    if (ptr >= s) {
      advance_write_ptr (&c->Out, ptr - (s - 448));
      ptr = get_write_ptr (&c->Out, 512);
      if (!ptr) return -1;
      s = ptr + 448;
    }
    
    *ptr++ = ',';  w++;
    w += t = sprintf (ptr, "%d%c%d", Res[0], ',', Res[1]);
    ptr += t;
    if (extra->need_rating) {
      w += t = sprintf (ptr, "%c%.6lf", ',', (double)*(float *)&Res[2]);
      ptr += t;
    }

    gather_heap_advance ();
    i++;
  }
  
  size_ptr[sprintf (size_ptr, "% 9d", w)] = '\r';
  //memcpy (ptr, "\r\nEND\r\n", 7);
  //ptr += 7;
  memcpy (ptr, "\r\n", 2);
  ptr+=2;
  advance_write_ptr (&c->Out, ptr - (s - 448));

  return 0;
}