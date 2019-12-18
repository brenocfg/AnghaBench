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
 int /*<<< orphan*/  end ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isOverrun(void * mem)
{
    Guard* guard = (Guard*)mem;
    char* memAsChar = (char*)mem;
    guard--;

    return strcmp(&memAsChar[guard->size], end) != 0;
}