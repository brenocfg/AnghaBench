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
struct TYPE_3__ {int idx_docs; unsigned long long* Md5_Pos; scalar_t__ Md5_Docs; } ;
typedef  TYPE_1__ volume_t ;

/* Variables and functions */
 unsigned long long const FILE_OFFSET_MASK ; 
 int STORAGE_ERR_DOC_NOT_FOUND ; 
 int STORAGE_ERR_WRONG_SECRET ; 
 unsigned long long STORAGE_SECRET_MASK ; 
 scalar_t__ memcmp (scalar_t__,unsigned char*,int) ; 

__attribute__((used)) static int md5_doc_idx_lookup (volume_t *V, unsigned char md5[16], unsigned long long secret, unsigned long long *file_pos) {
  int a, b, c;
  a = -1;
  b = V->idx_docs;
  while (b - a > 1) {
    c = ((a + b) >> 1);
    if (memcmp (V->Md5_Docs + (c << 4), &md5[0], 16) <= 0) { a = c; } else { b = c; }
  }
  if (a < 0 || memcmp (V->Md5_Docs + (a << 4), &md5[0], 16)) {
    return STORAGE_ERR_DOC_NOT_FOUND;
  }

  const unsigned long long pos = V->Md5_Pos[a];

  if ((secret ^ pos) & STORAGE_SECRET_MASK) {
    return STORAGE_ERR_WRONG_SECRET;
  }

  *file_pos = pos & FILE_OFFSET_MASK;

  return 0;
}