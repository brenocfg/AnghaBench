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
typedef  int /*<<< orphan*/  gzFile ;

/* Variables and functions */
 int gzwrite (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int tar_write_header (gzFile f, char b[512]) {
  unsigned chksum = 8 * 32; /* eight checksum bytes taken to be ascii spaces (decimal value 32) */
  int i;
  for (i = 0; i < 512; i++) {
    chksum += (unsigned char) b[i];
  }
  chksum &= 0777777;
  sprintf (b + 148, "%06o", chksum);
  b[155] = ' ';
  return gzwrite (f, b, 512) == 512 ? 0 : -1;
}