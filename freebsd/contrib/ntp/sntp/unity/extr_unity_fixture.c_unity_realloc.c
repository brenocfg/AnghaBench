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
struct TYPE_2__ {size_t size; } ;
typedef  TYPE_1__ Guard ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_FAIL_MESSAGE (char*) ; 
 scalar_t__ isOverrun (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  release_memory (void*) ; 
 int /*<<< orphan*/  unity_free (void*) ; 
 void* unity_malloc (size_t) ; 

void* unity_realloc(void * oldMem, size_t size)
{
    Guard* guard = (Guard*)oldMem;
//    char* memAsChar = (char*)oldMem;
    void* newMem;

    if (oldMem == 0)
        return unity_malloc(size);

    guard--;
    if (isOverrun(oldMem))
    {
        release_memory(oldMem);
        TEST_FAIL_MESSAGE("Buffer overrun detected during realloc()");
    }

    if (size == 0)
    {
        release_memory(oldMem);
        return 0;
    }

    if (guard->size >= size)
        return oldMem;

    newMem = unity_malloc(size);
    memcpy(newMem, oldMem, guard->size);
    unity_free(oldMem);
    return newMem;
}