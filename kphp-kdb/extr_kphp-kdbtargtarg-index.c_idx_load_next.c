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

/* Variables and functions */
 int RBuff ; 
 int RBuffEnd ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int idx_bytes ; 
 long long idx_cur_read_pos () ; 
 int /*<<< orphan*/  idx_fd ; 
 char* idx_filename ; 
 int idx_metafile_pos ; 
 int idx_read_pos ; 
 int idx_rptr ; 
 int /*<<< orphan*/  idx_slide_read_buffer () ; 
 int idx_wptr ; 
 int read (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,int,int) ; 

int idx_load_next (int need_bytes) {
  assert (need_bytes > 0 && need_bytes <= RBuffEnd - RBuff);
  long long idx_cur_pos = idx_cur_read_pos ();
  if (need_bytes + idx_cur_pos > idx_bytes) {
    need_bytes = idx_bytes - idx_cur_pos;
    assert (need_bytes >= 0);
    if (!need_bytes) {
      vkprintf (4, "failed at pos %lld, ends at %lld bytes, need %d\n", idx_cur_pos, idx_bytes, need_bytes);
      return 0;
    }
  }
  assert (idx_rptr >= RBuff && idx_rptr <= idx_wptr && idx_wptr <= RBuffEnd);
  if (idx_wptr >= idx_rptr + need_bytes) {
    return idx_wptr - idx_rptr;
  }
  if (idx_rptr + need_bytes > RBuffEnd) {
    idx_slide_read_buffer ();
    assert (idx_rptr + need_bytes <= RBuffEnd);
  }
  int to_load = RBuffEnd - idx_wptr;
  long long idx_wptr_pos = idx_cur_pos + (idx_wptr - idx_rptr);
  if (idx_wptr_pos + to_load > idx_bytes) {
    to_load = idx_bytes - idx_wptr_pos;
  }
  assert (to_load > 0);
  int r = read (idx_fd, idx_wptr, to_load);
  if (r != to_load) {
    fprintf (stderr, "error reading %d bytes from snapshot %s at position %lld: only %d bytes read: %m\n", to_load, idx_filename, idx_read_pos, r);
    assert (r == to_load);
  } else if (verbosity > 3) {
    fprintf (stderr, "preloaded %d bytes from snapshot at position %lld\n", r, idx_read_pos);
  }

  idx_wptr += r;
  idx_read_pos += r;
  idx_metafile_pos += r;
  return idx_wptr - idx_rptr;
}