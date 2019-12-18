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
typedef  int /*<<< orphan*/ * voidpf ;
struct TYPE_2__ {scalar_t__ error; int /*<<< orphan*/ * hf; } ;
typedef  TYPE_1__ WIN32FILE_IOWIN ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static voidpf win32_build_iowin(HANDLE hFile)
{
    voidpf ret=NULL;

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        WIN32FILE_IOWIN w32fiow;
        w32fiow.hf = hFile;
        w32fiow.error = 0;
        ret = malloc(sizeof(WIN32FILE_IOWIN));

        if (ret==NULL)
            CloseHandle(hFile);
        else
            *((WIN32FILE_IOWIN*)ret) = w32fiow;
    }
    return ret;
}