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
struct hash_entry {int next_used; char* key; char* data; int data_len; int next_entry; int key_len; int exp_time; int /*<<< orphan*/  key_hash; } ;
struct TYPE_3__ {char* key; int key_len; long long key_hash; char* data; int data_len; int exp_time; } ;
typedef  TYPE_1__ hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 size_t GET_ENTRY_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (int) ; 
 int /*<<< orphan*/  add_entry_time (int) ; 
 int /*<<< orphan*/  add_entry_used (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* buffer_stack ; 
 int /*<<< orphan*/  buffer_stack_size ; 
 int /*<<< orphan*/  del_entry_time (int) ; 
 int /*<<< orphan*/  del_entry_used (int) ; 
 struct hash_entry* entry_buffer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_entry (char*,int,long long) ; 
 TYPE_1__* get_entry_ptr (int) ; 
 long long get_hash (char*,int) ; 
 int get_new_entry () ; 
 int get_utime (int /*<<< orphan*/ ) ; 
 int* hash_st ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zzfree (char*,int) ; 
 void* zzmalloc (int) ; 

void write_stats (void) {
  int now = get_utime (CLOCK_MONOTONIC);

  int x = entry_buffer[0].next_used;
  struct hash_entry *entry = &entry_buffer[x];

  if (x == 0) {
    fprintf (stderr, "Memcached is empty\n");
    return;
  }

  char *key = zzmalloc (1024 + 3);
  key[0] = ' ';

  int j, k;
  while (x != 0 && entry->key[0] != ' ') {
    del_entry_used (x);
    del_entry_time (x);

    zzfree (entry->data, entry->data_len + 1);

    int *i = &hash_st[GET_ENTRY_ID (entry->key_hash)];

    while (*i != x && *i != -1) {
      i = &(entry_buffer[*i].next_entry);
    }

    assert (*i == x);

    *i = entry->next_entry;

    for (j = 0; j < entry->key_len && (entry->key[j] < '0' || entry->key[j] > '9') && entry->key[j] != '-' && entry->key[j] != ':'; j++) {
    }

    while (j > 1 && entry->key[j - 1] == '_') {
      j--;
    }

    int _count = 0, need_reduce_j = 0;
    for (k = j; k < entry->key_len; k++) {
      if (entry->key[k] == '_' && entry->key[k - 1] != '_') {
        _count++;
      }
      if (_count == 0 && entry->key[k] >= 'a' && entry->key[k] <= 'f') {
        need_reduce_j = 1;
      }
    }

    if (need_reduce_j) {
      while (j > 2 && entry->key[j - 1] >= 'a' && entry->key[j - 1] <= 'f') {
        j--;
      }
    }

    int key_len;

    if (j < entry->key_len && j < 1024 && entry->key_len > 0) {
      key_len = j + 3;

      memcpy (key + 1, entry->key, j);
      if (_count > 9) {
        _count = 9;
      }

      key[j + 1] = '0' + _count;
      key[j + 2] = (entry->key[j] != '_') * 2 + (entry->key[entry->key_len - 1] != '_') + '0';
    } else {
      key_len = 6;
      memcpy (key + 1, "OTHER", 5);
    }

    int size = key_len - 1 + 6 * sizeof (int) + 1;
    int left = entry->exp_time - now;

    long long key_hash = get_hash (key, key_len);
    int y = get_entry (key, key_len, key_hash);

    hash_entry_t *new_entry;

    if (y != -1) {
      new_entry = get_entry_ptr (y);

      del_entry_used (y);
    } else {
      y = get_new_entry ();
      new_entry = get_entry_ptr (y);

      new_entry->key = zzmalloc (key_len + 1);
      memcpy (new_entry->key, key, key_len);
      new_entry->key[key_len] = 0;

      new_entry->key_len = key_len;
      new_entry->key_hash = key_hash;

      add_entry (y);

      new_entry->data = zzmalloc (size);
      memset (new_entry->data, 0, sizeof (int) * 6);

      memcpy (new_entry->data + 6 * sizeof (int), new_entry->key + 1, key_len);
      new_entry->data_len = size - 1;
      new_entry->exp_time = 86400 + now;

      add_entry_time (y);
    }

    int *t = (int *)new_entry->data;
    t[0]++;
    t[1] += entry->key_len;
    t[2] += entry->data_len;
    t[3] += left / 500;
    t[4] += left % 500;
    if (left > t[5]) {
      t[5] = left;
    }

    add_entry_used (y);

    zzfree (entry->key, entry->key_len + 1);
    buffer_stack[buffer_stack_size++] = x;

    x = entry_buffer[0].next_used;
    entry = &entry_buffer[x];
  }

  zzfree (key, 1024 + 3);

  fprintf (stderr, "   quantity\ttot_key_len\ttot_val_len\t tot_memory\tmean_memory\t  mean_exp_time\tmax_exp_time\tprefix\n");
  int total[6] = {0};

  while (x != 0) {
    del_entry_used (x);
    del_entry_time (x);

    int *i = &hash_st[GET_ENTRY_ID (entry->key_hash)];

    while (*i != x && *i != -1) {
      i = &(entry_buffer[*i].next_entry);
    }

    assert (*i == x);

    *i = entry->next_entry;

    int *t = (int *)entry->data;

    fprintf (stderr, "%11d\t%11d\t%11d\t%11d\t%11.1lf\t%15.6lf\t%12d\t%s\n", t[0], t[1], t[2], t[1] + t[2] + (2 + (int)sizeof (struct hash_entry)) * t[0],
                                                                                   (t[1] + t[2]) * 1.0 / t[0] + (2 + sizeof (struct hash_entry)),
                                                                                   (t[3] * 500.0 + t[4]) / t[0], t[5], (char *)(t + 6));

    for (j = 0; j < 5; j++) {
      total[j] += t[j];
    }
    if (t[5] > total[5]) {
      total[5] = t[5];
    }

    zzfree (entry->key, entry->key_len + 1);
    zzfree (entry->data, entry->data_len + 1);
    buffer_stack[buffer_stack_size++] = x;

    x = entry_buffer[0].next_used;
    entry = &entry_buffer[x];
  }

  int *t = total;
  fprintf (stderr, "%11d\t%11d\t%11d\t%11d\t%11.1lf\t%15.6lf\t%12d\t%s\n", t[0], t[1], t[2], t[1] + t[2] + (2 + (int)sizeof (struct hash_entry)) * t[0],
                                                                                 (t[1] + t[2]) * 1.0 / t[0] + (2 + sizeof (struct hash_entry)),
                                                                                 (t[3] * 500.0 + t[4]) / t[0], t[5], "TOTAL");
}