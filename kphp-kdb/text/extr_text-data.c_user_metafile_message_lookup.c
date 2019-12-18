#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int user_id; } ;
typedef  TYPE_1__ user_t ;
struct file_user_header {int user_first_local_id; int user_last_local_id; int directory_offset; int data_offset; int extra_offset; } ;
struct file_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_message_size (struct file_message*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stderr ; 

struct file_message *user_metafile_message_lookup (char *metafile, int metafile_size, int local_id, user_t *U) {
  struct file_user_header *H = (struct file_user_header *) metafile;
  struct file_message *M;
  if (!metafile || metafile_size <= 0) {
    fprintf (stderr, "user_metafile_message_lookup (%p, %d, %d, %p [%d])\n", metafile, metafile_size, local_id, U, U->user_id);
  }
  assert (metafile && metafile_size > 0);
  if (local_id < H->user_first_local_id || local_id > H->user_last_local_id) {
    return 0;
  }
  int *p = (int *) (metafile + H->directory_offset) + (local_id - H->user_first_local_id);
  if (p[0] == p[1]) {
    return 0;
  }
  assert (p[0] >= H->data_offset && p[0] < p[1] && p[1] <= H->extra_offset);
  M = (struct file_message *) (metafile + p[0]);
  check_message_size (M, p[1] - p[0], 0);
  return M;
}