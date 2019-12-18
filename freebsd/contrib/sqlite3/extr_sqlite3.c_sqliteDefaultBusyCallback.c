#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int busyTimeout; int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int NDELAY ; 
 int /*<<< orphan*/  SQLITE_FCNTL_LOCK_TIMEOUT ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3OsFileControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3OsSleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sqliteDefaultBusyCallback(
  void *ptr,               /* Database connection */
  int count,               /* Number of times table has been busy */
  sqlite3_file *pFile      /* The file on which the lock occurred */
){
#if SQLITE_OS_WIN || HAVE_USLEEP
  /* This case is for systems that have support for sleeping for fractions of
  ** a second.  Examples:  All windows systems, unix systems with usleep() */
  static const u8 delays[] =
     { 1, 2, 5, 10, 15, 20, 25, 25,  25,  50,  50, 100 };
  static const u8 totals[] =
     { 0, 1, 3,  8, 18, 33, 53, 78, 103, 128, 178, 228 };
# define NDELAY ArraySize(delays)
  sqlite3 *db = (sqlite3 *)ptr;
  int tmout = db->busyTimeout;
  int delay, prior;

#ifdef SQLITE_ENABLE_SETLK_TIMEOUT
  if( sqlite3OsFileControl(pFile,SQLITE_FCNTL_LOCK_TIMEOUT,&tmout)==SQLITE_OK ){
    if( count ){
      tmout = 0;
      sqlite3OsFileControl(pFile, SQLITE_FCNTL_LOCK_TIMEOUT, &tmout);
      return 0;
    }else{
      return 1;
    }
  }
#else
  UNUSED_PARAMETER(pFile);
#endif
  assert( count>=0 );
  if( count < NDELAY ){
    delay = delays[count];
    prior = totals[count];
  }else{
    delay = delays[NDELAY-1];
    prior = totals[NDELAY-1] + delay*(count-(NDELAY-1));
  }
  if( prior + delay > tmout ){
    delay = tmout - prior;
    if( delay<=0 ) return 0;
  }
  sqlite3OsSleep(db->pVfs, delay*1000);
  return 1;
#else
  /* This case for unix systems that lack usleep() support.  Sleeping
  ** must be done in increments of whole seconds */
  sqlite3 *db = (sqlite3 *)ptr;
  int tmout = ((sqlite3 *)ptr)->busyTimeout;
  UNUSED_PARAMETER(pFile);
  if( (count+1)*1000 > tmout ){
    return 0;
  }
  sqlite3OsSleep(db->pVfs, 1000000);
  return 1;
#endif
}