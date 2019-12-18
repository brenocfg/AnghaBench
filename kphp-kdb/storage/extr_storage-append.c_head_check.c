#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ file_t ;

/* Variables and functions */
 scalar_t__ STORAGE_LEV_START_SIZE ; 
 int /*<<< orphan*/  crc32_complement ; 
 int /*<<< orphan*/  crc32_partial (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,scalar_t__) ; 
 scalar_t__ vk_pread (TYPE_1__*,unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int head_check (file_t *A, file_t *B) {
  if (B->size < STORAGE_LEV_START_SIZE) {
    return -10;
  }
  unsigned char a[STORAGE_LEV_START_SIZE], b[STORAGE_LEV_START_SIZE];
  if (vk_pread (A, a, STORAGE_LEV_START_SIZE, 0) < 0) {
    return -7;
  }
  if (vk_pread (B, b, STORAGE_LEV_START_SIZE, 0) < 0) {
    return -8;
  }
  if (memcmp (a, b, STORAGE_LEV_START_SIZE)) {
    kprintf ("%s isn't prefix of %s\n", B->filename, A->filename);
    return -9;
  }
  vkprintf (3, "First 36 bytes are equal (%s, %s).\n", A->filename, B->filename);
  crc32_complement = crc32_partial (a, STORAGE_LEV_START_SIZE, -1);
  return 0;
}