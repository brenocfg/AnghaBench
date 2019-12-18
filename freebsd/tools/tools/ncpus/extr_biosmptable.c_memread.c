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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  pfd ; 
 scalar_t__ pread (int /*<<< orphan*/ ,void*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  warn (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memread(off_t addr, void* entry, size_t size)
{
    if ((size_t)pread(pfd, entry, size, addr) != size) {
	warn("pread (%zu @ 0x%jx)", size, (intmax_t)addr);
	return 0;
    }
    return 1;
}