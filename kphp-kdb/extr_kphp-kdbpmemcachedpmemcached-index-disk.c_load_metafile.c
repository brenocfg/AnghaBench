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
struct metafile {char* data; long long* local_offsets; int /*<<< orphan*/ * aio; TYPE_1__* header; } ;
struct TYPE_2__ {int metafile_size; int nrecords; scalar_t__ local_offset; scalar_t__ global_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  WaitAioArrAdd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int allocated_metafile_bytes ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_aio_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_aio_read_connection (int /*<<< orphan*/ ,long long*,scalar_t__,int,int /*<<< orphan*/ *,struct metafile*) ; 
 int /*<<< orphan*/  ct_metafile_aio ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_metafiles () ; 
 int /*<<< orphan*/  idx_fd ; 
 int metafile_number ; 
 struct metafile* metafiles ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 scalar_t__ zzmalloc (int) ; 

void load_metafile (int metafile) {
  //WaitAio = NULL;
  WaitAioArrClear ();

  assert (metafile < metafile_number);

  struct metafile *meta = &metafiles[metafile];

  if (verbosity >= 3) {
    fprintf (stderr, "loading metafile %d in aio mode\n", metafile);
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
    }
  } else {
    if (verbosity >= 4) {
      fprintf (stderr, "No previous aio found for this metafile\n");
    }
  }

  if (meta->data) {
    fprintf (stderr, "Error: memory leak at load_metafile.\n");
    return;
  }                             

  free_metafiles ();

  //add_use (metafile);

  while (1) {
    meta->local_offsets = (long long *)zzmalloc (meta->header->metafile_size);
    if (meta->local_offsets != NULL) {
      meta->data = (char *)(meta->local_offsets + meta->header->nrecords);
      break;
    }
    fprintf (stderr, "no space to load metafile - cannot allocate %d bytes\n", meta->header->metafile_size);
  }

  allocated_metafile_bytes += meta->header->metafile_size;

  if (verbosity >= 4) {
    fprintf (stderr, "AIO query creating...\n");
  }
  meta->aio = create_aio_read_connection (idx_fd, meta->local_offsets, meta->header->global_offset + meta->header->local_offset, meta->header->metafile_size, &ct_metafile_aio, meta);
  if (verbosity >= 4) {
    fprintf (stderr, "AIO query created\n");
  }
  assert (meta->aio != NULL);
  //WaitAio = meta->aio;
  WaitAioArrAdd (meta->aio);

  return;
}