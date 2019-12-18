#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct metafile {int data; int /*<<< orphan*/ * aio; } ;
struct TYPE_2__ {int user_id; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WaitAioArrAdd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_aio_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_aio_read_connection (int /*<<< orphan*/ ,int,long long,long,int /*<<< orphan*/ *,struct metafile*) ; 
 int /*<<< orphan*/  ct_metafile_aio ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int free_by_LRU () ; 
 int /*<<< orphan*/  idx_fd ; 
 int index_large_data_offset ; 
 struct metafile* large_metafiles ; 
 TYPE_1__* large_users ; 
 int large_users_number ; 
 int metafile_alloc (long) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static void load_metafile_aio (int pos) {
  WaitAioArrClear ();
  //WaitAio = NULL;

  assert (0 <= pos && pos < large_users_number);
  assert (large_metafiles[pos].data);

  struct metafile *meta = &large_metafiles[pos];
  int user_id = large_users[pos].user_id;
  long data_len = sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset);
  long long idx_offset = index_large_data_offset + sizeof (long long) * (long long)large_users[pos].offset;

  if (verbosity >= 2) {
    fprintf (stderr, "loading metafile %d for user %d (%ld bytes at position %lld) in aio mode\n", pos, user_id, data_len, idx_offset);
  }

  if (meta->aio != NULL) {
    check_aio_completion (meta->aio);
    if (meta->aio != NULL) {
      //WaitAio = meta->aio;
      WaitAioArrAdd (meta->aio);
      return;
    }

    if (meta->data) {
      return;
    } else {
      fprintf (stderr, "Previous AIO query failed at %p, scheduling a new one\n", meta);
      while (!(meta->data = metafile_alloc (data_len))) {
        assert (free_by_LRU ());
      }
    }
  } else {
    if (verbosity >= 4) {
      fprintf (stderr, "No previous aio found for this metafile\n");
    }
  }

  if (verbosity >= 4) {
    fprintf (stderr, "AIO query creating...\n");
  }
  assert (meta->data);
  meta->aio = create_aio_read_connection (idx_fd, meta->data, idx_offset, data_len, &ct_metafile_aio, meta);
  if (verbosity >= 4) {
    fprintf (stderr, "AIO query created\n");
  }
  assert (meta->aio != NULL);
  //WaitAio = meta->aio;
  WaitAioArrAdd (meta->aio);

  return;
}