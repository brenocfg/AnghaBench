#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kfs_file_handle_t ;
typedef  int /*<<< orphan*/  index_header ;
struct TYPE_7__ {int log_split_min; int log_split_max; int log_split_mod; int magic; int /*<<< orphan*/  created_at; scalar_t__ log_pos1_crc32; scalar_t__ log_pos0_crc32; scalar_t__ log_timestamp; scalar_t__ log_pos1; scalar_t__ log_pos0; } ;
struct TYPE_6__ {int fd; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int SUPPORT_INDEX_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_index_header_size (TYPE_2__*) ; 
 TYPE_2__ header ; 
 int header_size ; 
 int log_split_max ; 
 int log_split_min ; 
 int log_split_mod ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int verbosity ; 

int load_header (kfs_file_handle_t Index) {
  if (Index == NULL) {
    fd[0] = -1;

    header.log_pos0 = 0;
    header.log_pos1 = 0;
    header.log_timestamp = 0;
    header.log_split_min = 0;
    header.log_split_max = 1;
    header.log_split_mod = 1;
    header.log_pos0_crc32 = 0;
    header.log_pos1_crc32 = 0;

    header.created_at = time (NULL);
    header_size = sizeof (index_header);

    return 0;
  }

  dbg ("load_header\n");

  fd[0] = Index->fd;
  int offset = Index->offset;

  //read header
  assert (lseek (fd[0], offset, SEEK_SET) == offset);

  int size = sizeof (index_header);
  int r = read (fd[0], &header, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position %d: %m\n", r, size, offset);
    assert (r == size);
  }

  if (header.magic != SUPPORT_INDEX_MAGIC) {
    fprintf (stderr, "bad support index file header\n");
    fprintf (stderr, "magic = 0x%08x // offset = %d\n", header.magic, offset);
    assert (0);
  }

  assert (header.log_split_max);
  log_split_min = header.log_split_min;
  log_split_max = header.log_split_max;
  log_split_mod = header.log_split_mod;

  header_size = get_index_header_size (&header);

  if (verbosity > 1) {
    fprintf (stderr, "header loaded %d %d %d %d\n", fd[0], log_split_min, log_split_max, log_split_mod);
    fprintf (stderr, "ok\n");
  }

  return 1;
}