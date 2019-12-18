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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes_read ; 
 int /*<<< orphan*/  crc64_partial (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_crc64_complement ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  readadv (size_t) ; 
 void* readin (size_t) ; 

void bread (void *b, size_t len) {
  void *p = readin (len);
  assert (p != NULL);
  memcpy (b, p, len);
  idx_crc64_complement = crc64_partial (b, len, idx_crc64_complement);
  readadv (len);
  bytes_read += len;
}