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
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int OFF_VERSION ; 
 int boot0bs (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
boot0version(const u_int8_t *bs)
{
    /* Check for old version, and return 0x100 if found. */
    int v = boot0bs(bs);
    if (v != 0)
        return v << 8;

    /* We have a newer boot0, so extract the version number and return it. */
    return *(const int *)(bs + OFF_VERSION) & 0xffff;
}