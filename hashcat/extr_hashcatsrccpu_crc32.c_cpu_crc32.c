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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int* crc32tab ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t hc_fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hcfree (int*) ; 
 scalar_t__ hcmalloc (int) ; 

int cpu_crc32 (const char *filename, u8 keytab[64])
{
  u32 crc = ~0u;

  FILE *fd = fopen (filename, "rb");

  #define MAX_KEY_SIZE (1024 * 1024)

  u8 *buf = (u8 *) hcmalloc (MAX_KEY_SIZE + 1);

  size_t nread = hc_fread (buf, sizeof (u8), MAX_KEY_SIZE, fd);

  fclose (fd);

  size_t kpos = 0;

  for (size_t fpos = 0; fpos < nread; fpos++)
  {
    crc = crc32tab[(crc ^ buf[fpos]) & 0xff] ^ (crc >> 8);

    keytab[kpos++] += (crc >> 24) & 0xff; if (kpos >= 64) kpos = 0;
    keytab[kpos++] += (crc >> 16) & 0xff; if (kpos >= 64) kpos = 0;
    keytab[kpos++] += (crc >>  8) & 0xff; if (kpos >= 64) kpos = 0;
    keytab[kpos++] += (crc >>  0) & 0xff; if (kpos >= 64) kpos = 0;
  }

  hcfree (buf);

  return 0;
}