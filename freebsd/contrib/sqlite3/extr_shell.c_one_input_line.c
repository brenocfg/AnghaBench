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
 char* continuePrompt ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* local_getline (char*,int /*<<< orphan*/ *) ; 
 char* mainPrompt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  shell_add_history (char*) ; 
 char* shell_readline (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char *one_input_line(FILE *in, char *zPrior, int isContinuation){
  char *zPrompt;
  char *zResult;
  if( in!=0 ){
    zResult = local_getline(zPrior, in);
  }else{
    zPrompt = isContinuation ? continuePrompt : mainPrompt;
#if SHELL_USE_LOCAL_GETLINE
    printf("%s", zPrompt);
    fflush(stdout);
    zResult = local_getline(zPrior, stdin);
#else
    free(zPrior);
    zResult = shell_readline(zPrompt);
    if( zResult && *zResult ) shell_add_history(zResult);
#endif
  }
  return zResult;
}