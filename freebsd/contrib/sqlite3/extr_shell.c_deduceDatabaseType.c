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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int SHELL_OPEN_APPENDVFS ; 
 int SHELL_OPEN_NORMAL ; 
 int SHELL_OPEN_UNSPEC ; 
 int SHELL_OPEN_ZIPFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ sqlite3_strlike (char*,char const*,int /*<<< orphan*/ ) ; 

int deduceDatabaseType(const char *zName, int dfltZip){
  FILE *f = fopen(zName, "rb");
  size_t n;
  int rc = SHELL_OPEN_UNSPEC;
  char zBuf[100];
  if( f==0 ){
    if( dfltZip && sqlite3_strlike("%.zip",zName,0)==0 ){
       return SHELL_OPEN_ZIPFILE;
    }else{
       return SHELL_OPEN_NORMAL;
    }
  }
  n = fread(zBuf, 16, 1, f);
  if( n==1 && memcmp(zBuf, "SQLite format 3", 16)==0 ){
    fclose(f);
    return SHELL_OPEN_NORMAL;
  }
  fseek(f, -25, SEEK_END);
  n = fread(zBuf, 25, 1, f);
  if( n==1 && memcmp(zBuf, "Start-Of-SQLite3-", 17)==0 ){
    rc = SHELL_OPEN_APPENDVFS;
  }else{
    fseek(f, -22, SEEK_END);
    n = fread(zBuf, 22, 1, f);
    if( n==1 && zBuf[0]==0x50 && zBuf[1]==0x4b && zBuf[2]==0x05
       && zBuf[3]==0x06 ){
      rc = SHELL_OPEN_ZIPFILE;
    }else if( n==0 && dfltZip && sqlite3_strlike("%.zip",zName,0)==0 ){
      rc = SHELL_OPEN_ZIPFILE;
    }
  }
  fclose(f);
  return rc;  
}