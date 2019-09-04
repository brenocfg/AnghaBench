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
typedef  int /*<<< orphan*/  endianess ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int checkFile (char const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* stdinName ; 

__attribute__((used)) static int checkFiles(const char** fnList, int fnTotal,
                      const endianess displayEndianess,
                      U32 strictMode,
                      U32 statusOnly,
                      U32 warn,
                      U32 quiet)
{
    int ok = 1;

    /* Special case for stdinName "-",
     * note: stdinName is not a string.  It's special pointer. */
    if (fnTotal==0) {
        ok &= checkFile(stdinName, displayEndianess, strictMode, statusOnly, warn, quiet);
    } else {
        int fnNb;
        for (fnNb=0; fnNb<fnTotal; fnNb++)
            ok &= checkFile(fnList[fnNb], displayEndianess, strictMode, statusOnly, warn, quiet);
    }
    return ok ? 0 : 1;
}