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
struct TYPE_4__ {int /*<<< orphan*/  pStack; } ;
typedef  TYPE_1__ FICL_VM ;

/* Variables and functions */
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  VE_GUESS ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int open (char*,int) ; 
 int stackPopINT (int /*<<< orphan*/ ) ; 
 char* stackPopPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stackPushINT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ verify_file (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmCheckStack (TYPE_1__*,int,int) ; 

__attribute__((used)) static void pfopen(FICL_VM *pVM)
{
    int     mode, fd, count;
    char    *ptr, *name;

#if FICL_ROBUST > 1
    vmCheckStack(pVM, 3, 1);
#endif

    mode = stackPopINT(pVM->pStack);    /* get mode */
    count = stackPopINT(pVM->pStack);   /* get count */
    ptr = stackPopPtr(pVM->pStack);     /* get ptr */

    if ((count < 0) || (ptr == NULL)) {
        stackPushINT(pVM->pStack, -1);
        return;
    }

    /* ensure that the string is null terminated */
    name = (char *)malloc(count+1);
    bcopy(ptr,name,count);
    name[count] = 0;

    /* open the file */
    fd = open(name, mode);
#ifdef LOADER_VERIEXEC
    if (fd >= 0) {
	if (verify_file(fd, name, 0, VE_GUESS) < 0) {
	    /* not verified writing ok but reading is not */
	    if ((mode & O_ACCMODE) != O_WRONLY) {
		close(fd);
		fd = -1;
	    }
	} else {
	    /* verified reading ok but writing is not */
	    if ((mode & O_ACCMODE) != O_RDONLY) {
		close(fd);
		fd = -1;
	    }
	}
    }
#endif
    free(name);
    stackPushINT(pVM->pStack, fd);
    return;
}