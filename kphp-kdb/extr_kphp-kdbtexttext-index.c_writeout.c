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
 int /*<<< orphan*/  crc32_acc ; 
 int /*<<< orphan*/  crc32_partial (void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flushout () ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 
 int metafile_pos ; 
 int wptr ; 
 int write_pos ; 

void writeout (const void *D, size_t len) {
  const char *d = D;
  crc32_acc = crc32_partial (D, len, crc32_acc); 
  while (len > 0) {
    int r = Buff + BUFFSIZE - wptr;
    if (r > len) { 
      r = len; 
    }
    memcpy (wptr, d, r);
    d += r;
    wptr += r;
    write_pos += r;
    metafile_pos += r;
    len -= r;
    if (len > 0) {
      flushout();
    }
  }
}