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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileCheck (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argCount, const char** argv) {
    int argNb = 1;
    int testCCtxParams = 0;
    if (argCount < 2) {
        fprintf(stderr, "Error : no argument : need input file \n");
        exit(9);
    }

    if (!strcmp(argv[argNb], "--cctxParams")) {
      testCCtxParams = 1;
      argNb++;
    }

    fileCheck(argv[argNb], testCCtxParams);
    fprintf(stderr, "no pb detected\n");
    return 0;
}