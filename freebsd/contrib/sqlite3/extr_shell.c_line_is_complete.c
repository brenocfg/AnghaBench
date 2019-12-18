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
 int sqlite3_complete (char*) ; 

__attribute__((used)) static int line_is_complete(char *zSql, int nSql){
  int rc;
  if( zSql==0 ) return 1;
  zSql[nSql] = ';';
  zSql[nSql+1] = 0;
  rc = sqlite3_complete(zSql);
  zSql[nSql] = 0;
  return rc;
}