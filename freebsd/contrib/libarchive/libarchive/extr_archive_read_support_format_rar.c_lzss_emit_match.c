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
struct TYPE_4__ {unsigned char* window; int position; } ;
struct rar {TYPE_1__ lzss; } ;

/* Variables and functions */
 int lzss_current_offset (TYPE_1__*) ; 
 int lzss_mask (TYPE_1__*) ; 
 int lzss_size (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static inline void
lzss_emit_match(struct rar *rar, int offset, int length)
{
  int dstoffs = lzss_current_offset(&rar->lzss);
  int srcoffs = (dstoffs - offset) & lzss_mask(&rar->lzss);
  int l, li, remaining;
  unsigned char *d, *s;

  remaining = length;
  while (remaining > 0) {
    l = remaining;
    if (dstoffs > srcoffs) {
      if (l > lzss_size(&rar->lzss) - dstoffs)
        l = lzss_size(&rar->lzss) - dstoffs;
    } else {
      if (l > lzss_size(&rar->lzss) - srcoffs)
        l = lzss_size(&rar->lzss) - srcoffs;
    }
    d = &(rar->lzss.window[dstoffs]);
    s = &(rar->lzss.window[srcoffs]);
    if ((dstoffs + l < srcoffs) || (srcoffs + l < dstoffs))
      memcpy(d, s, l);
    else {
      for (li = 0; li < l; li++)
        d[li] = s[li];
    }
    remaining -= l;
    dstoffs = (dstoffs + l) & lzss_mask(&(rar->lzss));
    srcoffs = (srcoffs + l) & lzss_mask(&(rar->lzss));
  }
  rar->lzss.position += length;
}