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
struct stat {int dummy; } ;

/* Variables and functions */
 int lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  statTimesToUtc (char const*,struct stat*) ; 

__attribute__((used)) static int fileLinkStat(
  const char *zPath,
  struct stat *pStatBuf
){
#if defined(_WIN32)
  int rc = lstat(zPath, pStatBuf);
  if( rc==0 ) statTimesToUtc(zPath, pStatBuf);
  return rc;
#else
  return lstat(zPath, pStatBuf);
#endif
}