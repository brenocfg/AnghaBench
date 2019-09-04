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
struct index_header_v2 {scalar_t__ magic; scalar_t__ log_pos1_crc32; scalar_t__ log_pos1; scalar_t__ log_timestamp; } ;
typedef  TYPE_1__* kfs_file_handle_t ;
struct TYPE_3__ {int fd; } ;

/* Variables and functions */
 scalar_t__ STATSX_INDEX_MAGIC_OLD ; 
 scalar_t__ STATSX_INDEX_MAGIC_V1 ; 
 scalar_t__ STATSX_INDEX_MAGIC_V2 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 scalar_t__ jump_log_ts ; 
 int /*<<< orphan*/  read (int,struct index_header_v2*,int) ; 
 int /*<<< orphan*/  stderr ; 

int load_index (kfs_file_handle_t Index) {
  if (Index == NULL) {
    jump_log_ts = 0;
    jump_log_pos = 0;
    jump_log_crc32 = 0;
    return 0;
  }
  int idx_fd = Index->fd;
  struct index_header_v2 header;
  read (idx_fd, &header, sizeof (struct index_header_v2));
  if (header.magic !=  STATSX_INDEX_MAGIC_V1 && header.magic != STATSX_INDEX_MAGIC_OLD && header.magic !=  STATSX_INDEX_MAGIC_V1 + 1 && header.magic != STATSX_INDEX_MAGIC_V2 && header.magic != STATSX_INDEX_MAGIC_V2) {
    fprintf (stderr, "index file is not for statsx\n");
    return -1;
  }

  jump_log_ts = header.log_timestamp;
  jump_log_pos = header.log_pos1;
  jump_log_crc32 = header.log_pos1_crc32;
  return 1;
}