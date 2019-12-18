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
typedef  int /*<<< orphan*/  dword_t ;
struct TYPE_2__ {int /*<<< orphan*/  egid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*) ; 
 TYPE_1__* current ; 

dword_t sys_getegid32() {
    STRACE("getegid32()");
    return current->egid;
}