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
 int /*<<< orphan*/  TESTMGR_POISON_BYTE ; 
 int /*<<< orphan*/ * memchr_inv (void const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline bool testmgr_is_poison(const void *addr, size_t len)
{
	return memchr_inv(addr, TESTMGR_POISON_BYTE, len) == NULL;
}