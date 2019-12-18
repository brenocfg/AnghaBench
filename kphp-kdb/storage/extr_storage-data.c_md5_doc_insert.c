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
struct TYPE_4__ {int /*<<< orphan*/  docs; int /*<<< orphan*/  Md5_Root; } ;
typedef  TYPE_1__ volume_t ;

/* Variables and functions */
 int STORAGE_ERR_DOC_EXISTS ; 
 int STORAGE_ERR_WRONG_SECRET ; 
 unsigned long long STORAGE_SECRET_MASK ; 
 int /*<<< orphan*/  lrand48 () ; 
 int md5_doc_lookup (TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  md5_tree_insert (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  tot_docs ; 
 int /*<<< orphan*/  vkprintf (int,char*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static int md5_doc_insert (volume_t *V, unsigned char md5[16], unsigned long long secret, unsigned long long file_pos) {
  vkprintf (3, "md5_doc_insert (secret = %llx, file_pos = %llx)\n", secret, file_pos);
  unsigned long long tmp;
  int r = md5_doc_lookup (V, md5, 0, &tmp);
  if (!r || r == STORAGE_ERR_WRONG_SECRET) {
    return STORAGE_ERR_DOC_EXISTS;
  }
  V->Md5_Root = md5_tree_insert (V->Md5_Root, md5, lrand48 (), file_pos | (secret & STORAGE_SECRET_MASK));
  V->docs++;
  tot_docs++;
  return 0;
}