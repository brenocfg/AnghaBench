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
struct archive_read {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 char* RAR_SIGNATURE ; 
 char* __archive_read_ahead (struct archive_read*,int,int*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 

__attribute__((used)) static int
archive_read_format_rar_bid(struct archive_read *a, int best_bid)
{
  const char *p;

  /* If there's already a bid > 30, we'll never win. */
  if (best_bid > 30)
	  return (-1);

  if ((p = __archive_read_ahead(a, 7, NULL)) == NULL)
    return (-1);

  if (memcmp(p, RAR_SIGNATURE, 7) == 0)
    return (30);

  if ((p[0] == 'M' && p[1] == 'Z') || memcmp(p, "\x7F\x45LF", 4) == 0) {
    /* This is a PE file */
    ssize_t offset = 0x10000;
    ssize_t window = 4096;
    ssize_t bytes_avail;
    while (offset + window <= (1024 * 128)) {
      const char *buff = __archive_read_ahead(a, offset + window, &bytes_avail);
      if (buff == NULL) {
        /* Remaining bytes are less than window. */
        window >>= 1;
        if (window < 0x40)
          return (0);
        continue;
      }
      p = buff + offset;
      while (p + 7 < buff + bytes_avail) {
        if (memcmp(p, RAR_SIGNATURE, 7) == 0)
          return (30);
        p += 0x10;
      }
      offset = p - buff;
    }
  }
  return (0);
}