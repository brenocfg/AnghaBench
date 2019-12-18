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
 int SQLITE_ERROR ; 
 int SQLITE_N_KEYWORD ; 
 int SQLITE_OK ; 
 int* aKWLen ; 
 int* aKWOffset ; 
 char* zKWText ; 

int sqlite3_keyword_name(int i,const char **pzName,int *pnName){
  if( i<0 || i>=SQLITE_N_KEYWORD ) return SQLITE_ERROR;
  *pzName = zKWText + aKWOffset[i];
  *pnName = aKWLen[i];
  return SQLITE_OK;
}