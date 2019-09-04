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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__* Snapshot ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_top ; 
 long long idx_bytes ; 
 long long idx_fsize ; 
 scalar_t__ idx_kfs_headers_size ; 
 long long idx_loaded_bytes ; 
 long long kfs_read_file (TYPE_1__*,char*,long long) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*,long long,long long,long long) ; 
 void* zmalloc (long long) ; 
 void* zzmalloc (long long) ; 

void *load_metafile (void *data, long long offset, long long size, long max_size) {
  assert (size >= 0 && size <= (long long) (dyn_top - dyn_cur));
//  assert (size <= max_size || !max_size);
  assert (offset >= 0 && offset <= idx_fsize && offset + size <= idx_fsize);
  if (data == (void *)-1) {
    data = zzmalloc (size);
  }
  if (!data) {
    data = zmalloc (size);
    idx_bytes += size;
  }
  assert (lseek (Snapshot->fd, offset + idx_kfs_headers_size, SEEK_SET) == offset + idx_kfs_headers_size);
  char *r_data = data;
  while (size > 0) {
    long long r = kfs_read_file (Snapshot, r_data, size);
    if (r <= 0) {
      vkprintf (0, "error reading data from index file: read %lld bytes instead of %lld at position %lld: %m\n", r, size, offset + (r_data - (char *)data));
      assert (r == size);
      return 0;
    }
    r_data += r;
    size -= r;
    idx_loaded_bytes += r;
  }
  return data;
}