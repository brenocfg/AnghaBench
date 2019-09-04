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
struct metafile {struct aio_connection* aio; scalar_t__ data; } ;
struct connection {int dummy; } ;
struct aio_connection {scalar_t__ basic_type; scalar_t__ extra; } ;
struct TYPE_2__ {int user_id; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_use (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ct_aio ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int index_large_data_offset ; 
 struct metafile* large_metafiles ; 
 TYPE_1__* large_users ; 
 int large_users_number ; 
 int /*<<< orphan*/  metafile_free (scalar_t__,int) ; 
 int /*<<< orphan*/  metafiles_load_errors ; 
 int /*<<< orphan*/  metafiles_load_success ; 
 int /*<<< orphan*/  metafiles_loaded ; 
 int /*<<< orphan*/  stderr ; 
 int tot_aio_loaded_bytes ; 
 int verbosity ; 

int onload_metafile (struct connection *c, int read_bytes) {
  if (verbosity >= 2) {
    fprintf (stderr, "onload_metafile(%p,%d)\n", c, read_bytes);
  }

  struct aio_connection *a = (struct aio_connection *)c;
  struct metafile *meta = (struct metafile *) a->extra;

  assert (a->basic_type == ct_aio);
  assert (meta != NULL);

  if (meta->aio != a) {
    fprintf (stderr, "assertion (meta->aio == a) will fail\n");
    fprintf (stderr, "%p != %p\n", meta->aio, a);
  }

  assert (meta->aio == a);

  int pos = meta - large_metafiles;
  assert (0 <= pos && pos < large_users_number);

  if (verbosity >= 2) {
    fprintf (stderr, "*** Read metafile %d for large user %d : read %d bytes at position %lld\n", pos, large_users[pos].user_id, read_bytes, index_large_data_offset + sizeof (long long) * (long long)large_users[pos].offset);
  }

  if (read_bytes != sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset)) {
    if (verbosity >= 0) {
      fprintf (stderr, "ERROR reading metafile %d for large user %d at position %lld: read %d bytes out of %ld: %m\n", pos, large_users[pos].user_id, index_large_data_offset + sizeof (long long) * (long long)large_users[pos].offset, read_bytes, (long)sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset));
    }
    meta->aio = NULL;
    metafile_free (meta->data, sizeof (long long) * (large_users[pos + 1].offset - large_users[pos].offset));
    meta->data = 0;
    metafiles_load_errors ++;
  } else {
    meta->aio = NULL;
    metafiles_loaded ++;
    add_use (pos);
    metafiles_load_success ++;
    tot_aio_loaded_bytes += read_bytes;
  }
  return 1;
}