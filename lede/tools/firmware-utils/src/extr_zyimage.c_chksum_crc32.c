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
typedef  unsigned long u_int32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned long* crc_tab ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 unsigned long fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szbuf ; 

u_int32_t chksum_crc32 (FILE *f)
{
  register unsigned long crc;
  unsigned long i, j;
  char *buffer = malloc(szbuf);
  char *buf;

  crc = 0xFFFFFFFF;
  while (!feof(f))
  {
    j = fread(buffer, 1, szbuf, f);
    buf = buffer;
    for (i = 0; i < j; i++)
      crc = ((crc >> 8) & 0x00FFFFFF) ^ crc_tab[(crc ^ *buf++) & 0xFF];
  }
  free(buffer);
  return crc;
}