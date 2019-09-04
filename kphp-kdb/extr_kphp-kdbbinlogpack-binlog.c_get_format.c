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
#define  kfs_bzf_bz2 130 
#define  kfs_bzf_xz 129 
#define  kfs_bzf_zlib 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *get_format (int format) {
  switch (format) {
    case kfs_bzf_zlib: return "gz";
    case kfs_bzf_bz2: return "bzip";
    case kfs_bzf_xz: return "xz";
  }
  static char buf[32];
  sprintf (buf, "unknown (%d)", format);
  return buf;
}