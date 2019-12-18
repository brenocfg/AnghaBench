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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  tar_fill_ustar_magic (char*) ; 

__attribute__((used)) static int tar_fill_longlink_header (char b[512], int link_length, char ext) {
  memset (b, 0, 512);
  strcpy (b, "././@LongLink");
  sprintf (b + 100, "%07o", 0);
  sprintf (b + 108, "%07o", 0);
  sprintf (b + 116, "%07o", 0);
  sprintf (b + 124, "%011o", link_length + 1);
  sprintf (b + 136, "%011llo", (unsigned long long) 0);
  tar_fill_ustar_magic (b);
  b[156] = ext;
  return 0;
}