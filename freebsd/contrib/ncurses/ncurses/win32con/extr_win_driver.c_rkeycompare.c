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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int LOWORD (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
rkeycompare(const void *el1, const void *el2)
{
    WORD key1 = (LOWORD((*((const LONG *) el1)))) & 0x7fff;
    WORD key2 = (LOWORD((*((const LONG *) el2)))) & 0x7fff;

    return ((key1 < key2) ? -1 : ((key1 == key2) ? 0 : 1));
}