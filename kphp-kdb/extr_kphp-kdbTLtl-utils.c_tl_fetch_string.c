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
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 char* tl_zzmalloc (unsigned int) ; 

int tl_fetch_string (int *in_ptr, int ilen, char **s, int *slen, int allocate_new_cstr) {
  *s = NULL;
  int *in_end = in_ptr + ilen;
  if (in_ptr >= in_end) {
    return -1;
  }
  unsigned l = *in_ptr;
  if ((l & 0xff) < 0xfe) {
    l &= 0xff;
    if (slen) {
      *slen = l;
    }
    if (in_end >= in_ptr + (l >> 2) + 1) {
      char *src = ((char *) in_ptr) + 1;
      if (allocate_new_cstr) {
        *s = tl_zzmalloc (l + 1);
        memcpy (*s, src, l);
        (*s)[l] = 0;
      } else {
        *s = src;
      }
      return (l >> 2) + 1;
    } else {
      return -1;
    }
  } else if ((l & 0xff) == 0xfe) {
    l >>= 8;
    if (slen) {
      *slen = l;
    }
    if (l >= 0xfe && in_end >= in_ptr + ((l + 7) >> 2)) {
      char *src = (char *) &in_ptr[1];
      if (allocate_new_cstr) {
        *s = tl_zzmalloc (l + 1);
        memcpy (*s, src, l);
        (*s)[l] = 0;
      } else {
        *s = src;
      }
      return (l + 7) >> 2;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}