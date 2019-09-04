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
struct TYPE_6__ {int /*<<< orphan*/  Md5_Root; } ;
typedef  TYPE_1__ volume_t ;
struct TYPE_7__ {unsigned long long offset; } ;
typedef  TYPE_2__ md5_tree_t ;

/* Variables and functions */
 unsigned long long const FILE_OFFSET_MASK ; 
 int STORAGE_ERR_DOC_NOT_FOUND ; 
 int STORAGE_ERR_WRONG_SECRET ; 
 unsigned long long STORAGE_SECRET_MASK ; 
 int md5_doc_idx_lookup (TYPE_1__*,unsigned char*,unsigned long long,unsigned long long*) ; 
 TYPE_2__* md5_tree_lookup (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,unsigned long long const) ; 

__attribute__((used)) static int md5_doc_lookup (volume_t *V, unsigned char md5[16], unsigned long long secret, unsigned long long *file_pos) {
  int r = md5_doc_idx_lookup (V, md5, secret, file_pos);
  if (!r || r == STORAGE_ERR_WRONG_SECRET) {
    return r;
  }
  vkprintf (3, "md5_doc_idx_lookup returns exit code %d.\n", r);

  md5_tree_t *T = md5_tree_lookup (V->Md5_Root, md5);
  if (T == NULL) {
    return STORAGE_ERR_DOC_NOT_FOUND;
  }

  const unsigned long long pos = T->offset;
  vkprintf (4, "pos = %llx\n", pos);

  if ((secret ^ pos) & STORAGE_SECRET_MASK) {
    return STORAGE_ERR_WRONG_SECRET;
  }

  *file_pos = pos & FILE_OFFSET_MASK;

  return 0;
}