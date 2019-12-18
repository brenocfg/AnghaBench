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
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  shell_out_of_memory () ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_win32_mbcs_to_utf8_v2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ stdin_is_interactive ; 
 int strlen30 (char*) ; 

__attribute__((used)) static char *local_getline(char *zLine, FILE *in){
  int nLine = zLine==0 ? 0 : 100;
  int n = 0;

  while( 1 ){
    if( n+100>nLine ){
      nLine = nLine*2 + 100;
      zLine = realloc(zLine, nLine);
      if( zLine==0 ) shell_out_of_memory();
    }
    if( fgets(&zLine[n], nLine - n, in)==0 ){
      if( n==0 ){
        free(zLine);
        return 0;
      }
      zLine[n] = 0;
      break;
    }
    while( zLine[n] ) n++;
    if( n>0 && zLine[n-1]=='\n' ){
      n--;
      if( n>0 && zLine[n-1]=='\r' ) n--;
      zLine[n] = 0;
      break;
    }
  }
#if defined(_WIN32) || defined(WIN32)
  /* For interactive input on Windows systems, translate the
  ** multi-byte characterset characters into UTF-8. */
  if( stdin_is_interactive && in==stdin ){
    char *zTrans = sqlite3_win32_mbcs_to_utf8_v2(zLine, 0);
    if( zTrans ){
      int nTrans = strlen30(zTrans)+1;
      if( nTrans>nLine ){
        zLine = realloc(zLine, nTrans);
        if( zLine==0 ) shell_out_of_memory();
      }
      memcpy(zLine, zTrans, nTrans);
      sqlite3_free(zTrans);
    }
  }
#endif /* defined(_WIN32) || defined(WIN32) */
  return zLine;
}