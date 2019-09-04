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
struct metafile {int size; int flags; struct aio_connection* aio; scalar_t__ data; int /*<<< orphan*/  cnt; } ;
struct connection {int dummy; } ;
struct aio_connection {scalar_t__ basic_type; scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ct_aio ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  onload_counter (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tot_aio_fails ; 
 int tot_aio_loaded_bytes ; 
 int tot_user_metafile_bytes ; 
 int /*<<< orphan*/  tot_user_metafiles ; 
 int verbosity ; 
 int /*<<< orphan*/  zzfree (scalar_t__,int) ; 

int onload_metafile (struct connection *c, int read_bytes) {
  if (verbosity > 2) {
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

  if (read_bytes != meta->size) {
    if (verbosity >= 0) {
      fprintf (stderr, "ERROR reading metafile (counter %lld): read %d bytes out of %lld: %m\n", meta->cnt, read_bytes, meta->size);
    }
    zzfree (meta->data, meta->size);
    meta->data = 0;
    meta->aio = 0;
    tot_aio_fails ++;
    meta->flags |= 1;
    return 0;
  }
  assert(read_bytes == meta->size);

  tot_aio_loaded_bytes += read_bytes;



  if (verbosity > 2) {
    fprintf (stderr, "*** Read metafile: read %d bytes\n", read_bytes);
  }

  onload_counter (meta->data, meta->size, meta->cnt, 0);

  zzfree(meta->data, meta->size);
  meta->data = 0;

  meta->aio = NULL;
  meta->flags &= ~1;
  
  tot_user_metafile_bytes += meta->size;
  tot_user_metafiles++;
  
  return 1;
}