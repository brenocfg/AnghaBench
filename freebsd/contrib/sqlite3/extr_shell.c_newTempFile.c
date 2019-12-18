#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_4__ {scalar_t__ zTempFile; scalar_t__ db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_TEMPFILENAME ; 
 int /*<<< orphan*/  clearTempFile (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_file_control (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 void* sqlite3_mprintf (char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,scalar_t__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void newTempFile(ShellState *p, const char *zSuffix){
  clearTempFile(p);
  sqlite3_free(p->zTempFile);
  p->zTempFile = 0;
  if( p->db ){
    sqlite3_file_control(p->db, 0, SQLITE_FCNTL_TEMPFILENAME, &p->zTempFile);
  }
  if( p->zTempFile==0 ){
    sqlite3_uint64 r;
    sqlite3_randomness(sizeof(r), &r);
    p->zTempFile = sqlite3_mprintf("temp%llx.%s", r, zSuffix);
  }else{
    p->zTempFile = sqlite3_mprintf("%z.%s", p->zTempFile, zSuffix);
  }
  if( p->zTempFile==0 ){
    raw_printf(stderr, "out of memory\n");
    exit(1);
  }
}