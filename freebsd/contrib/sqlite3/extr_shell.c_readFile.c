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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (long) ; 

__attribute__((used)) static char *readFile(const char *zName, int *pnByte){
  FILE *in = fopen(zName, "rb");
  long nIn;
  size_t nRead;
  char *pBuf;
  if( in==0 ) return 0;
  fseek(in, 0, SEEK_END);
  nIn = ftell(in);
  rewind(in);
  pBuf = sqlite3_malloc64( nIn+1 );
  if( pBuf==0 ){ fclose(in); return 0; }
  nRead = fread(pBuf, nIn, 1, in);
  fclose(in);
  if( nRead!=1 ){
    sqlite3_free(pBuf);
    return 0;
  }
  pBuf[nIn] = 0;
  if( pnByte ) *pnByte = nIn;
  return pBuf;
}