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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  getaddflags16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getaddflags32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getaddflags64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getaddflags8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long
getaddflags(int opsize, uint64_t x, uint64_t y)
{
	KASSERT(opsize == 1 || opsize == 2 || opsize == 4 || opsize == 8,
	    ("getaddflags: invalid operand size %d", opsize));

	if (opsize == 1)
		return (getaddflags8(x, y));
	else if (opsize == 2)
		return (getaddflags16(x, y));
	else if (opsize == 4)
		return (getaddflags32(x, y));
	else
		return (getaddflags64(x, y));
}