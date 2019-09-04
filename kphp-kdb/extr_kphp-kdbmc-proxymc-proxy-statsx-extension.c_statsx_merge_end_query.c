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
struct statsx_gather_extra {int flags; scalar_t__ Q_raw; } ;
struct gather_entry {int res_bytes; int num; scalar_t__* data; } ;
struct connection {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int FLAG_BAD_SERVERS ; 
 int FLAG_COUNTER ; 
 int FLAG_DOUBLE ; 
 int FLAG_MONTHLY ; 
 int FLAG_NO_SERIALIZE ; 
 int FLAG_ONE_INT ; 
 int FLAG_UNION ; 
 int Q_bad_servers ; 
 scalar_t__ Q_raw ; 
 int bad_servers ; 
 char* buff ; 
 int /*<<< orphan*/  clear_gather_heap (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  gather_heap_advance () ; 
 int /*<<< orphan*/  gather_heap_insert (struct gather_entry*) ; 
 int /*<<< orphan*/  gather_sum_res (struct gather_entry*,struct statsx_gather_extra*) ; 
 int get_counter_serialized (char*,struct statsx_gather_extra*) ; 
 int* get_gather_heap_head () ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int statsx_merge_end_query (struct connection *c, const char *key, int key_len, void *E, struct gather_entry *data, int tot_num) {
  struct statsx_gather_extra *extra = E;
  Q_raw = extra->Q_raw;

  int i;
  int one_int = extra->flags & FLAG_ONE_INT;
  int union_mode = extra->flags & FLAG_UNION;
  Q_bad_servers = extra->flags & FLAG_BAD_SERVERS;
  int to_serialize = !(extra->flags & FLAG_NO_SERIALIZE);
  int monthly = extra->flags & FLAG_MONTHLY;
  int counter_mode = extra->flags & FLAG_COUNTER;
  bad_servers = 0;
  
  if (verbosity >= 4) {
	  fprintf (stderr, "one_int = %d, union_mode = %d\n", one_int, union_mode);
	}
  int res = 0;

  clear_gather_heap (extra->flags & FLAG_DOUBLE);

  for (i = 0; i < tot_num; i++) if (data[i].res_bytes > 0) {
  	//fprintf (stderr, "!!!");
    if (!one_int) {
      if (!union_mode) {
        gather_sum_res (&data[i], extra);
      } else {
        gather_heap_insert (&data[i]);
      }
    } else {
      if (data[i].res_bytes >= 4) {
        res += data[i].data[0];
      }
    }
  } else {
    if (data[i].num == -1) {
      bad_servers ++;
    }
    if (verbosity >= 4) {
      fprintf (stderr, "Dropping result %d (num = %d)\n", i, data[i].num);
    }
  }
  

  if (union_mode) {
    res = 0;
    int last = -1;
    long long last_res = 0;
    if (!Q_raw && Q_bad_servers) {
      if (res) {
        buff[res ++] = ',';
      }
      res += sprintf (buff + res, "%d", bad_servers);
    }
    while (res < 100000) {
      int *t = get_gather_heap_head ();
      if (!t) {
        break;
      }
      if (last == *t) {
        if (monthly) {
          last_res += *(t + 1);
        }
        gather_heap_advance ();
        continue;
      }
      if (last != -1) {
        if (monthly) {
          if (Q_raw) {
            *(int *)(buff + res) = last_res;
            res += 4;
          } else {
            if (res) {
              buff[res ++] = ',';
            }
            res += sprintf (buff + res, "%lld", last_res);
          }
        }
        if (Q_raw) {
          *(int *)(buff + res) = last;
          res += 4;
        } else {
          if (res) {
            buff[res ++] = ',';
          }
          if (!monthly) {
            res += sprintf (buff + res, "%d", last);
          } else {
            res += sprintf (buff + res, "%d,%d", last % 100, last / 100);
          }
        }
      }
      last = *t;
      last_res = *(t + 1);
      gather_heap_advance ();
    }
    if (last != -1) {
      if (monthly) {
        if (Q_raw) {
          *(int *)(buff + res) = last_res;
          res += 4;
        } else {
          if (res) {
            buff[res ++] = ',';
          }
          res += sprintf (buff + res, "%lld", last_res);
        }
      }
      if (Q_raw) {
        *(int *)(buff + res) = last;
        res += 4;
      } else {
        if (res) {
          buff[res ++] = ',';
        }
        if (!monthly) {
          res += sprintf (buff + res, "%d", last);
        } else {
          res += sprintf (buff + res, "%d,%d", last % 100, last / 100);
        }
      }
    }
  }

  if (counter_mode) {
    res = get_counter_serialized (buff, extra);
  }
  


  if (one_int) {
    to_serialize = 0;
    if (!Q_raw) {
      if (!Q_bad_servers) {
        res = sprintf (buff, "%d", res);
      } else {
        res = sprintf (buff, "%d,%d", bad_servers, res);
      }
    } else {      
      *(int *)buff = res;
      res = 4;
    }
  }
  if (to_serialize && !Q_raw && !union_mode) {
    write_out (&c->Out, buff+res, sprintf (buff+res, "VALUE %s 1 %d\r\n", key, res));
  } else {
    write_out (&c->Out, buff+res, sprintf (buff+res, "VALUE %s 0 %d\r\n", key, res));
  }
  write_out (&c->Out, buff, res);
  write_out (&c->Out, "\r\n", 2);

  return 0;
}