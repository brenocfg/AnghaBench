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
struct msg_buffers_chunk {scalar_t__ magic; scalar_t__* free_cnt; int two_power; int free_buffers; int tot_buffers; int buffer_size; scalar_t__ first_buffer; struct msg_buffers_chunk* ch_next; struct msg_buffers_chunk* ch_prev; } ;
struct msg_buffer {int refcnt; int /*<<< orphan*/  magic; struct msg_buffers_chunk* chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_BUFFER_USED_MAGIC ; 
 scalar_t__ MSG_CHUNK_HEAD_MAGIC ; 
 struct msg_buffers_chunk* alloc_new_msg_buffers_chunk (struct msg_buffers_chunk*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int get_buffer_no (struct msg_buffers_chunk*,struct msg_buffer*) ; 
 scalar_t__ lrand48 () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  total_used_buffers ; 
 int total_used_buffers_size ; 
 int verbosity ; 

struct msg_buffer *alloc_msg_buffer_internal (struct msg_buffer *neighbor, struct msg_buffers_chunk *CH) {
  assert (CH->magic == MSG_CHUNK_HEAD_MAGIC);
  struct msg_buffers_chunk *CF = CH->ch_next, *C = CF;
  if (C == CH) {
    C = alloc_new_msg_buffers_chunk (CH);
    if (!C) {
      return 0;
    }
    assert (C == CH->ch_next && C != CH && C->free_cnt[1]);
  } else while (C != CH && !C->free_cnt[1]) {
    CH->ch_next = C->ch_next;
    C->ch_next->ch_prev = CH;
    C->ch_next = CH;
    C->ch_prev = CH->ch_prev;
    C->ch_prev->ch_next = C;
    CH->ch_prev = C;
    C = CH->ch_next;
    if (C == CF) {
      C = alloc_new_msg_buffers_chunk (CH);
      if (!C) {
	return 0;
      }
      assert (C == CH->ch_next && C != CH && C->free_cnt[1]);
      break;
    }
  }

  int two_power = C->two_power, i = 1;

  if (neighbor && neighbor->chunk == C) {
    int x = get_buffer_no (C, neighbor);
    if (verbosity > 2) {
      fprintf (stderr, "alloc_msg_buffer: allocating neighbor buffer for %d\n", x);
    }
    int j = 1, k = 0, l = 0, r = two_power;
    while (i < two_power) {
      i <<= 1;
      int m = (l + r) >> 1;
      if (x < m) {
	if (C->free_cnt[i] > 0) {
	  r = m;
	  if (C->free_cnt[i+1] > 0) {
	    j = i + 1;
	  }
	} else {
	  l = m;
	  i++;
	}
      } else if (C->free_cnt[i+1] > 0) {
	l = m;
	i++;
      } else {
	k = i = j;
	while (i < two_power) {
	  i <<= 1;
	  if (!C->free_cnt[i]) {
	    i++;
	  }
	  assert (-- C->free_cnt[i] >= 0);
	}
	break;
      }
    }
    if (!k) {
      k = i;
    }
    while (k > 0) {
      assert (-- C->free_cnt[k] >= 0);
      k >>= 1;
    }
  } else {
    int j = C->free_cnt[1] < 16 ? C->free_cnt[1] : 16;
    j = ((long long) lrand48() * j) >> 31;
    assert (j >= 0 && j < C->free_cnt[1]);
    while (i < two_power) {
      assert (-- C->free_cnt[i] >= 0);
      i <<= 1;
      if (C->free_cnt[i] <= j) {
	j -= C->free_cnt[i];
	i++;
      }
    }
    assert (-- C->free_cnt[i] == 0);
  }

  -- CH->free_buffers;

  i -= two_power;
  if (verbosity > 2) {
    fprintf (stderr, "alloc_msg_buffer(%d): tot_buffers = %d, free_buffers = %d\n", i, C->tot_buffers, C->free_buffers);
  }
  assert (i >= 0 && i < C->tot_buffers);

  struct msg_buffer *X = (struct msg_buffer *) ((char *) C->first_buffer + i * (C->buffer_size + 16));

  X->chunk = C;
  X->refcnt = 1;
  X->magic = MSG_BUFFER_USED_MAGIC;

  total_used_buffers_size += C->buffer_size;
  total_used_buffers ++;
  // assert (get_buffer_no (C, X) == i);

  return X;
}