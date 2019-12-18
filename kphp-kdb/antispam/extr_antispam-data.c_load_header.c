#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kfs_file_handle_t ;
struct TYPE_8__ {int log_split_max; int log_split_mod; int magic; int log_split_min; int /*<<< orphan*/  created_at; } ;
typedef  TYPE_2__ index_header ;
struct TYPE_7__ {int fd; int offset; } ;

/* Variables and functions */
 int ANTISPAM_INDEX_MAGIC ; 
 int FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int log_split_max ; 
 int log_split_min ; 
 int log_split_mod ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int verbosity ; 

__attribute__((used)) static bool load_header (kfs_file_handle_t Index, index_header* header) {
  int fd = -1;
  if (Index == NULL) {
    memset (header, 0, sizeof (index_header));
    header->created_at = time (NULL);
    header->log_split_max = 1;
    header->log_split_mod = 1;
    return TRUE;
  }

  fd = Index->fd;
  int offset = Index->offset;

  // reading header
  if (lseek (fd, offset, SEEK_SET) != offset) {
    fprintf (stderr, "error reading header from index file: incorrect Index->offset = %d: %m\n", offset);
    return FALSE;
  }

  int size = sizeof (index_header);
  int r = read (fd, header, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position %d: %m\n", r, size, offset);
    return FALSE;
  }

  if (header->magic != ANTISPAM_INDEX_MAGIC) {
    fprintf (stderr, "bad antispam index file header\n");
    fprintf (stderr, "magic = 0x%08x instead of 0x%08x // offset = %d\n", header->magic, ANTISPAM_INDEX_MAGIC, offset);
    return FALSE;
  }

  assert (header->log_split_max);
  log_split_min = header->log_split_min;
  log_split_max = header->log_split_max;
  log_split_mod = header->log_split_mod;

  if (verbosity > 1) {
    fprintf (stderr, "header loaded %d %d %d %d\n", fd, log_split_min, log_split_max, log_split_mod);
    fprintf (stderr, "ok\n");
  }
  return TRUE;
}