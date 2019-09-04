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

/* Variables and functions */
 int BUFFSIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t bytes_read ; 
 int /*<<< orphan*/  crc32_partial (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_crc32_complement ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  readadv (size_t) ; 
 void* readin (size_t) ; 

__attribute__((used)) static void bread (void *b, size_t len) {
  unsigned bs = BUFFSIZE >> 1;
  while (len > 0) {
    size_t l = len;
    if (l > bs) { l = bs; }
    void *p = readin (l);
    assert (p != NULL);
    memcpy (b, p, l);
    idx_crc32_complement = crc32_partial (b, l, idx_crc32_complement);
    b += l;
    readadv (l);
    bytes_read += l;
    len -= l;
  }
}