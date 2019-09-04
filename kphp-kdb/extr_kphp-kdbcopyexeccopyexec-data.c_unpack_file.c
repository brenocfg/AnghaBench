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
typedef  int /*<<< orphan*/  uLongf ;
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
struct lev_copyexec_aux_transaction_cmd_file {scalar_t__ filename_size; scalar_t__ crc32; int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  size; int /*<<< orphan*/  compressed_size; scalar_t__ data; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ PATH_MAX ; 
 scalar_t__ Z_OK ; 
 scalar_t__ compute_crc32 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_close (int*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ lcopy_attrs (scalar_t__*,struct stat*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,scalar_t__) ; 
 int open (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (scalar_t__*,char) ; 
 scalar_t__ uncompress (void*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__* unpack_filename_buff ; 
 int /*<<< orphan*/  write (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unpack_file (struct lev_copyexec_aux_transaction_cmd_file *E) {
  unpack_filename_buff[0] = 0;
  if (E->filename_size < 0 || E->filename_size >= PATH_MAX) {
    return -__LINE__;
  }
  memcpy (unpack_filename_buff, E->data, E->filename_size);
  unpack_filename_buff[E->filename_size] = 0;
  if (strchr (unpack_filename_buff, '/') != NULL) {
    return -__LINE__;
  }
  void *d = malloc (E->size);
  if (d == NULL) {
    return -__LINE__;
  }

  uLongf destLen = E->size;
  if (Z_OK != uncompress (d, &destLen, (unsigned char *) E->data + E->filename_size, E->compressed_size)) {
    free (d);
    return -__LINE__;
  }

  if (destLen != E->size || compute_crc32 (d, E->size) != E->crc32) {
    free (d);
    return -__LINE__;
  }

  int fd = open (unpack_filename_buff, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, E->mode);
  if (fd < 0) {
    return -__LINE__;
  }

  if (write (fd, d, E->size) != E->size) {
    free (d);
    fd_close (&fd);
    return -__LINE__;
  }
  free (d);
  fd_close (&fd);
  //copy file attributes
  struct stat st;
  st.st_mode = E->mode;
  st.st_uid = E->uid;
  st.st_gid = E->gid;
  st.st_atime = E->actime;
  st.st_mtime = E->modtime;
  if (lcopy_attrs (unpack_filename_buff, &st) < 0) {
    return -__LINE__;
  }
  return 0;
}