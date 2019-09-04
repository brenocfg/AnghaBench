#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  index_header ;
struct TYPE_5__ {scalar_t__ magic; TYPE_1__* data; int /*<<< orphan*/  created_at; } ;
struct TYPE_4__ {scalar_t__ drive_old_mx; scalar_t__ drive_r; scalar_t__ drive_l; } ;

/* Variables and functions */
 scalar_t__ LETTERS_INDEX_MAGIC ; 
 int MAX_PRIORITY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_close_file (int /*<<< orphan*/ ) ; 
 scalar_t__ dl_open_file (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ header ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int verbosity ; 

int load_index (char *index_name) {
  if (index_name == NULL || dl_open_file (0, index_name, -1) < 0) {
    header.magic = LETTERS_INDEX_MAGIC;
    header.created_at = time (NULL);

    int i;
    for (i = 0; i < MAX_PRIORITY; i++) {
      header.data[i].drive_l = header.data[i].drive_r = header.data[i].drive_old_mx = 0;
    }
    return 0;
  }

  assert (lseek (fd[0], 0, SEEK_SET) == 0);

  int size = sizeof (index_header);
  int r = read (fd[0], &header, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d: %m\n", r, size);
  }
  assert (r == size);

  if (header.magic != LETTERS_INDEX_MAGIC) {
    fprintf (stderr, "bad letters index file header\n");
    assert (0);
  }

  if (verbosity > 1) {
    fprintf (stderr, "header loaded\n");
  }

  dl_close_file (0);
  return 1;
}