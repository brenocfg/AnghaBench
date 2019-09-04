#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t readto_off; size_t type; TYPE_7__* F; } ;
typedef  TYPE_2__ stream_t ;
typedef  size_t ssize_t ;
struct TYPE_11__ {int /*<<< orphan*/  fd; TYPE_1__* info; } ;
struct TYPE_10__ {size_t* total_bytes_read; } ;
struct TYPE_8__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 size_t KFS_BINLOG_ZIP_CHUNK_SIZE ; 
 size_t PREVSIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  assert (int) ; 
 void* backup_buff ; 
 void* io_buff ; 
 scalar_t__ kfs_bz_decode (TYPE_7__*,size_t,void*,int*,int*) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,size_t,...) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t read (int /*<<< orphan*/ ,void*,size_t) ; 
 TYPE_6__ stats ; 
 scalar_t__ stream_is_zipped (TYPE_2__*) ; 
 size_t stream_tell (TYPE_2__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static int stream_read (stream_t *S, void *buff, size_t size) {
  int disk_bytes_read = size;
  if (stream_is_zipped (S)) {
    assert (buff == backup_buff || buff == &io_buff[PREVSIZE] || buff == io_buff);
    int s = KFS_BINLOG_ZIP_CHUNK_SIZE > size ? KFS_BINLOG_ZIP_CHUNK_SIZE : size;
    if (kfs_bz_decode (S->F, S->readto_off, buff, &s, &disk_bytes_read) < 0) {
      kprintf ("kfs_bz_decode file '%s' from offset %lld failed.\n", S->F->info->filename, S->readto_off);
      return -1;
    }
    if (s < size) {
      kprintf ("kfs_bz_decode file '%s' from offset %lld retuned %d bytes, expected %d bytes.\n", S->F->info->filename, S->readto_off, s, (int) size);
      return -1;
    }
  } else {
    ssize_t s = read (S->F->fd, buff, size);
    if (s != size) {
      if (s < 0) {
        kprintf ("read '%s' from offset %lld fail. %m\n", S->F->info->filename, stream_tell (S));
        return -1;
      } else {
        stats.total_bytes_read[S->type] += s;
        kprintf ("read '%s' from offset %lld. Read %lld bytes of expected %lld.\n", S->F->info->filename, stream_tell (S), (long long) s, (long long) size);
        vkprintf (2, "lseek (%d, 0, SEEK_CUR) = %lld\n", S->F->fd, (long long ) lseek (S->F->fd, 0, SEEK_CUR));
        return -1;
      }
    }
  }
  stats.total_bytes_read[S->type] += disk_bytes_read;
  S->readto_off += size;
  return size;
}