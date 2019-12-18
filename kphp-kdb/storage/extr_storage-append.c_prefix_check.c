#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lev_crc32 {scalar_t__ type; int /*<<< orphan*/  crc32; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ file_t ;
typedef  int /*<<< orphan*/  C1 ;

/* Variables and functions */
 scalar_t__ LEV_CRC32 ; 
 int STORAGE_LEV_START_SIZE ; 
 int /*<<< orphan*/  crc32_complement ; 
 int /*<<< orphan*/  crc32_partial (struct lev_crc32*,int,int /*<<< orphan*/ ) ; 
 int head_check (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ local_id ; 
 scalar_t__ memcmp (struct lev_crc32*,struct lev_crc32*,int) ; 
 scalar_t__ vk_pread (TYPE_1__*,struct lev_crc32*,int,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int prefix_check (file_t *A, file_t *B) {
  if (A->size < B->size) {
    kprintf ("%s is smaller than %s\n", A->filename, B->filename);
    return -2;
  }
  if (A->size < 20 || B->size < 20) {
    return -1;
  }

  int r = head_check (A, B);
  if (r < 0) {
    return r;
  }

  if (B->size == STORAGE_LEV_START_SIZE) {
    local_id = 0;
    return 0;
  }

  struct lev_crc32 C1, C2;
  int sz = sizeof (C1);
  long long off = B->size - sz;
  if (vk_pread (A, &C1, sz, off) < 0) {
    return -3;
  }
  if (vk_pread (B, &C2, sz, off) < 0) {
    return -4;
  }
  crc32_complement = ~C1.crc32;
  if (C1.type != LEV_CRC32) {
    kprintf ("didn't find LEV_CRC32 record in %s at offset %lld\n", A->filename, off);
    return -5;
  }

  if (memcmp (&C1, &C2, sz)) {
    kprintf ("last lev_crc32 record don't matched.\n");
    return -6;
  }
  vkprintf (3, "Last %d bytes are equal (%s, %s).\n", sz, A->filename, B->filename);
  crc32_complement = crc32_partial (&C1, sz, crc32_complement);
  return 0;
}