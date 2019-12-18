#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; scalar_t__ aio; } ;
struct TYPE_3__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  add_use (int) ; 
 scalar_t__ allocated_metafiles_size ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int free_by_LRU () ; 
 int /*<<< orphan*/  idx_fd ; 
 scalar_t__ index_large_data_offset ; 
 TYPE_2__* large_metafiles ; 
 TYPE_1__* large_users ; 
 int large_users_number ; 
 int /*<<< orphan*/  load_metafile_aio (int) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ max_allocated_metafiles_size ; 
 scalar_t__ metafile_alloc (long long) ; 
 int /*<<< orphan*/  metafiles_cache_loading ; 
 int /*<<< orphan*/  metafiles_cache_miss ; 
 int /*<<< orphan*/  metafiles_cache_ok ; 
 int /*<<< orphan*/  metafiles_loaded ; 
 scalar_t__ read (int /*<<< orphan*/ ,scalar_t__,long long) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int load_metafile (int pos, int use_aio) {
  assert (0 <= pos && pos < large_users_number);

  if (use_aio < 0 && large_metafiles[pos].data && large_metafiles[pos].aio) {
    if (verbosity >= 0) {
      fprintf (stderr, "forced re-loading of pending aio query for large metafile %d without aio\n", pos);
    }
    // --- MEMORY LEAK for case if aio is really active ---
    // we don't free buffer so that aio might finish loading data, then it will fail in onload_metafile(), but no data corruption will occur
    // metafile_free (large_metafiles[pos].data, sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset));
    large_metafiles[pos].data = 0;
    large_metafiles[pos].aio = 0;
  }

  if (large_metafiles[pos].data) {
    if (large_metafiles[pos].aio) {
      load_metafile_aio (pos);
      metafiles_cache_loading ++;
      if (!large_metafiles[pos].aio) {
        return 1;
      } else {
        return -2;
      }
    }
    if (use_aio > 0) {
      metafiles_cache_ok ++;
    }
    return 1;
  }

  assert (!large_metafiles[pos].aio);

  long long len = sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset);
  while (allocated_metafiles_size + len > max_allocated_metafiles_size && free_by_LRU ());
  while (!(large_metafiles[pos].data = metafile_alloc (len))) {
    assert (free_by_LRU ());
  }

  if (use_aio <= 0) {
    //fprintf (stderr, "%lld - %lu\n", index_large_data_offset + sizeof (long long) * (long long)large_users[pos].offset, sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset));
    lseek (idx_fd, index_large_data_offset + sizeof (long long) * (long long)large_users[pos].offset, SEEK_SET);
    assert ((long long)(read (idx_fd, large_metafiles[pos].data, len)) == len);
    add_use (pos);
    metafiles_loaded ++;
    return 1;
  } else {
    load_metafile_aio (pos);
    metafiles_cache_miss ++;
    return -2;
  }
  return 0;
}