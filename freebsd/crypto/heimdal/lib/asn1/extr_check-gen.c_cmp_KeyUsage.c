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
typedef  int /*<<< orphan*/  KeyUsage ;

/* Variables and functions */
 scalar_t__ KeyUsage2int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp_KeyUsage (void *a, void *b)
{
    KeyUsage *aa = a;
    KeyUsage *ab = b;

    return KeyUsage2int(*aa) != KeyUsage2int(*ab);
}