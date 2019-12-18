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
 int Buff ; 
 int /*<<< orphan*/  crc32c_partial (void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  idx_crc32c_complement ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 
 int wptr ; 

__attribute__((used)) static int writeout (const void *D, size_t len) {
  idx_crc32c_complement = crc32c_partial (D, len, idx_crc32c_complement);
  const int res = len;
  const char *d = D;
  while (len > 0) {
    int r = Buff + BUFFSIZE - wptr;
    if (r > len) {
      r = len;
    }
    memcpy (wptr, d, r);
    d += r;
    wptr += r;
    len -= r;
    if (len > 0) {
      flushout ();
    }
  }
  return res;
}