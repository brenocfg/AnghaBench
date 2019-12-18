#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_index_data ;
typedef  TYPE_1__* kfs_file_handle_t ;
typedef  int /*<<< orphan*/  index_header ;
struct TYPE_11__ {int /*<<< orphan*/  cnt; scalar_t__ ngood; scalar_t__ nbad; } ;
struct TYPE_10__ {int user_cnt; int log_split_min; int log_split_max; int log_split_mod; scalar_t__ teach_messages; scalar_t__ black_list_size; struct TYPE_10__* user_index; int /*<<< orphan*/  created_at; scalar_t__ log_pos1_crc32; scalar_t__ log_pos0_crc32; scalar_t__ log_timestamp; scalar_t__ log_pos1; scalar_t__ log_pos0; } ;
struct TYPE_9__ {int fd; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bayes_global_load (TYPE_6__*) ; 
 int /*<<< orphan*/  black_list_load (scalar_t__) ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_index_header_size (TYPE_2__*) ; 
 TYPE_6__ global_bayes ; 
 TYPE_2__ header ; 
 int header_size ; 
 int log_split_max ; 
 int log_split_min ; 
 int log_split_mod ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_words ; 
 int /*<<< orphan*/  qhtbl_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qhtbl_set_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* qmalloc (int) ; 
 int read (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ teach_messages ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int verbosity ; 

int load_header (kfs_file_handle_t Index) {
  if (Index == NULL) {
    fd[0] = -1;

    header.user_cnt = 0;
    header.user_index = NULL;

    header.log_pos0 = 0;
    header.log_pos1 = 0;
    header.log_timestamp = 0;
    header.log_split_min = 0;
    header.log_split_max = 1;
    header.log_split_mod = 1;
    header.log_pos0_crc32 = 0;
    header.log_pos1_crc32 = 0;

    header.teach_messages = 0;
    header.black_list_size = 0;

    header.created_at = time (NULL);
    header_size = sizeof (index_header);

    global_bayes.nbad = global_bayes.ngood = 0;
    qhtbl_init (&global_bayes.cnt);
    qhtbl_set_size (&global_bayes.cnt, max_words);

    return 0;
  }

  fd[0] = Index->fd;
  int offset = Index->offset;

  //read header
  assert (lseek (fd[0], offset, SEEK_SET) == offset);

  int size = sizeof (index_header) - sizeof (long);
  int r = read (fd[0], &header, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d at position %d: %m\n", r, size, offset);
    assert (r == size);
  }

  size = sizeof (user_index_data) * (header.user_cnt + 1);
  header.user_index = qmalloc (size);

  r = read (fd[0], header.user_index, size);
  if (r != size) {
    fprintf (stderr, "error reading header from index file: read %d bytes instead of %d: %m\n", r, size);
    assert (r == size);
  }

  assert (header.log_split_max);
  log_split_min = header.log_split_min;
  log_split_max = header.log_split_max;
  log_split_mod = header.log_split_mod;

  header_size = get_index_header_size (&header) - sizeof (long);

  bayes_global_load (&global_bayes);
  black_list_load (header.black_list_size);

  teach_messages = header.teach_messages;

  if (verbosity > 1) {
    fprintf (stderr, "header loaded %d %d %d %d\n", fd[0], log_split_min, log_split_max, log_split_mod);
    fprintf (stderr, "ok\n");
  }
  return 1;
}