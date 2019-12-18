#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** freeBlocks; int /*<<< orphan*/ * memBlocks; scalar_t__ busyBlocks; scalar_t__ freeMemSize; int /*<<< orphan*/  h_Spinlock; } ;
typedef  TYPE_1__ t_MM ;
typedef  TYPE_1__* t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFreeBlock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * CreateNewBlock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MAKE_ALIGNED (scalar_t__,int) ; 
 int /*<<< orphan*/  MM_Free (TYPE_1__*) ; 
 int MM_MAX_ALIGNMENT ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_InitSpinlock () ; 
 scalar_t__ XX_Malloc (int) ; 

t_Error MM_Init(t_Handle *h_MM, uint64_t base, uint64_t size)
{
    t_MM        *p_MM;
    uint64_t    newBase, newSize;
    int         i;

    if (!size)
    {
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Size (should be positive)"));
    }

    /* Initializes a new MM object */
    p_MM = (t_MM *)XX_Malloc(sizeof(t_MM));
    if (!p_MM)
    {
        RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
    }

    p_MM->h_Spinlock = XX_InitSpinlock();
    if (!p_MM->h_Spinlock)
    {
        XX_Free(p_MM);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MM spinlock!"));
    }

    /* Initializes counter of free memory to total size */
    p_MM->freeMemSize = size;

    /* A busy list is empty */
    p_MM->busyBlocks = 0;

    /* Initializes a new memory block */
    if ((p_MM->memBlocks = CreateNewBlock(base, size)) == NULL)
    {
        MM_Free(p_MM);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
    }

    /* Initializes a new free block for each free list*/
    for (i=0; i <= MM_MAX_ALIGNMENT; i++)
    {
        newBase = MAKE_ALIGNED( base, (0x1 << i) );
        newSize = size - (newBase - base);

        if ((p_MM->freeBlocks[i] = CreateFreeBlock(newBase, newSize)) == NULL)
        {
            MM_Free(p_MM);
            RETURN_ERROR(MAJOR, E_NO_MEMORY, NO_MSG);
        }
    }

    *h_MM = p_MM;

    return (E_OK);
}