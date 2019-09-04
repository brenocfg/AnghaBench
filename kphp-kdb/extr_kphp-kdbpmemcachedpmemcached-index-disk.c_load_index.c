#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct metafile_header_old {int dummy; } ;
struct metafile_header {int dummy; } ;
typedef  TYPE_2__* kfs_file_handle_t ;
struct TYPE_14__ {scalar_t__ magic; size_t nrecords; int key_len; scalar_t__ log_pos1_crc32; scalar_t__ log_pos1; scalar_t__ log_timestamp; } ;
typedef  TYPE_3__ index_header ;
struct TYPE_16__ {TYPE_4__* header; int /*<<< orphan*/ * aio; scalar_t__ local_offsets; scalar_t__ data; } ;
struct TYPE_15__ {int nrecords; int /*<<< orphan*/  metafile_size; TYPE_3__* key; } ;
struct TYPE_13__ {TYPE_1__* info; int /*<<< orphan*/  fd; } ;
struct TYPE_12__ {scalar_t__ file_size; } ;

/* Variables and functions */
 size_t MAX_METAFILES ; 
 scalar_t__ PMEMCACHED_INDEX_MAGIC ; 
 scalar_t__ PMEMCACHED_INDEX_MAGIC_OLD ; 
 int /*<<< orphan*/  PMEMCACHED_TYPE_INDEX_DISK ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  idx_fd ; 
 scalar_t__ index_size ; 
 int /*<<< orphan*/  index_type ; 
 int init_memory ; 
 scalar_t__ jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 scalar_t__ jump_log_ts ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_3__*,int) ; 
 TYPE_3__ metafile_header_tmp ; 
 int metafile_mode ; 
 size_t metafile_number ; 
 TYPE_7__* metafiles ; 
 size_t* next_use ; 
 int /*<<< orphan*/  pmemcached_register_replay_logevent () ; 
 size_t* prev_use ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int snapshot_size ; 
 int /*<<< orphan*/  stderr ; 
 int tot_records ; 
 int /*<<< orphan*/  upgrade_header (TYPE_3__*) ; 
 int use_metafile_crc32 ; 
 int verbosity ; 
 TYPE_4__* zzmalloc (int) ; 

int load_index (kfs_file_handle_t Index) {
  index_type = PMEMCACHED_TYPE_INDEX_DISK;
  prev_use[MAX_METAFILES] = MAX_METAFILES;
  next_use[MAX_METAFILES] = MAX_METAFILES;
  if (Index == NULL) {
    index_size = 0;
    jump_log_ts = 0;
    jump_log_pos = 0;
    jump_log_crc32 = 0;
    snapshot_size = 0;
    return 0;
  }
  metafile_mode = 1;
  idx_fd = Index->fd;
  index_header header;
  read (idx_fd, &header, sizeof (index_header));
  if (header.magic !=  PMEMCACHED_INDEX_MAGIC && header.magic != PMEMCACHED_INDEX_MAGIC_OLD) {
    fprintf (stderr, "index file is not for pmemcached\n");
    return -1;
  }
  int old_metafiles = (header.magic == PMEMCACHED_INDEX_MAGIC_OLD);
  use_metafile_crc32 = !old_metafiles;
  jump_log_ts = header.log_timestamp;
  jump_log_pos = header.log_pos1;
  jump_log_crc32 = header.log_pos1_crc32;
  
  metafile_number = header.nrecords;
  if (verbosity>=2){
    fprintf (stderr, "%d metafiles readed\n", header.nrecords);
  }
  if (metafile_number > MAX_METAFILES) {
    fprintf (stderr, "Fatal: too many metafiles\n");
    return -1;
  }

  int i;
  tot_records = 0;
  for (i = 0; i < metafile_number; i++) {
    if (old_metafiles) {
      read (idx_fd, &metafile_header_tmp, sizeof (struct metafile_header_old));      
      upgrade_header (&metafile_header_tmp);
    } else {
      read (idx_fd, &metafile_header_tmp, sizeof (struct metafile_header));
    }
    metafiles[i].header = zzmalloc (sizeof (struct metafile_header) + metafile_header_tmp.key_len);
    init_memory += sizeof (struct metafile_header) + metafile_header_tmp.key_len;
    memcpy (metafiles[i].header, &metafile_header_tmp, sizeof (struct metafile_header));
    metafiles[i].data = 0;
    metafiles[i].local_offsets = 0;
    metafiles[i].aio = NULL;
    read (idx_fd, metafiles[i].header->key, metafile_header_tmp.key_len);
    lseek (idx_fd, metafiles[i].header->metafile_size, SEEK_CUR);
    if (verbosity >= 3) {
      fprintf (stderr, "read metafile %d\n", i);
      fprintf (stderr, "number of records = %d\n", metafiles[i].header->nrecords);
    }
    tot_records += metafiles[i].header->nrecords;
  }

  if (verbosity) {
    fprintf (stderr, "Total %lld records in index\n", tot_records);
  }
  index_size = Index->info->file_size;
  snapshot_size = init_memory;

  pmemcached_register_replay_logevent();
  return 0;
}