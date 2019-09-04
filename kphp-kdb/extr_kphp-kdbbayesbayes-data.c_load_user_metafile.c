#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int metafile_len; struct aio_connection* aio; int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_2__ user ;
struct connection {int dummy; } ;
struct aio_connection {void* basic_type; TYPE_2__* extra; } ;
struct TYPE_9__ {int user_cnt; TYPE_1__* user_index; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/ * EMPTY__METAFILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct aio_connection* WaitAio ; 
 int allocated_metafile_bytes ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_aio_completion (struct aio_connection*) ; 
 struct aio_connection* create_aio_read_connection (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* ct_aio ; 
 int /*<<< orphan*/  ct_metafile_aio ; 
 int debug_on ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_memory_used () ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 TYPE_5__ header ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onload_user_metafile (struct connection*,int) ; 
 int /*<<< orphan*/ * qmalloc (int) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ user_loaded (TYPE_2__*) ; 
 int verbosity ; 

void load_user_metafile (user *u, int local_id, int no_aio) {
  static struct aio_connection empty_aio_conn;

  no_aio |= debug_on;
  WaitAio = NULL;

  if (user_loaded (u)) {
    return;
  }

  if (local_id > header.user_cnt || header.user_index[local_id].size == 0) {
    u->metafile = EMPTY__METAFILE;
    u->metafile_len = 12;

    empty_aio_conn.extra = u;
    empty_aio_conn.basic_type = ct_aio;
    u->aio = &empty_aio_conn;

    onload_user_metafile ((struct connection *)(&empty_aio_conn), u->metafile_len);
    return;
  }

  if (u->aio != NULL) {
    check_aio_completion (u->aio);
    if (u->aio != NULL) {
      WaitAio = u->aio;
      return;
    }

    if (u->metafile) {
      return;
    } else {
      fprintf (stderr, "Previous AIO query failed for user at %p, scheduling a new one\n", u);
    }
  }

  u->metafile_len = header.user_index[local_id].size;
  u->metafile = qmalloc (u->metafile_len);
  if (u->metafile == NULL) {
    fprintf (stderr, "no space to load metafile - cannot allocate %d bytes (%lld currently used)\n", u->metafile_len, (long long)get_memory_used());
    assert (0);
  }
  allocated_metafile_bytes += u->metafile_len;

  if (verbosity > 2) {
    fprintf (stderr, "*** Scheduled reading user data from index %d at position %lld, %d bytes, noaio = %d\n", fd[0], header.user_index[local_id].shift, u->metafile_len, no_aio);
  }

  assert (1 <= local_id && local_id <= header.user_cnt);
  if (no_aio) {
    double disk_time = -get_utime (CLOCK_MONOTONIC);

    assert (lseek (fd[0], header.user_index[local_id].shift, SEEK_SET) == header.user_index[local_id].shift);
    int size = header.user_index[local_id].size;
    int r = read (fd[0], u->metafile, size);
    if (r != size) {
      fprintf (stderr, "error reading user %d from index file: read %d bytes instead of %d at position %lld: %m\n", local_id, r, size, header.user_index[local_id].shift);
      assert (r == size);
    }

    disk_time += get_utime (CLOCK_MONOTONIC);
    if (verbosity > 2) {
      fprintf (stderr, "  disk time = %.6lf\n", disk_time);
    }

    empty_aio_conn.extra = u;
    empty_aio_conn.basic_type = ct_aio;
    u->aio = &empty_aio_conn;

    assert (u->aio != NULL);

    onload_user_metafile ((struct connection *)(&empty_aio_conn), u->metafile_len);
  } else {
    u->aio = create_aio_read_connection (fd[0], u->metafile, header.user_index[local_id].shift, u->metafile_len, &ct_metafile_aio, u);
    assert (u->aio != NULL);
    WaitAio = u->aio;
  }

  return;
}