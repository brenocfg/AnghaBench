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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int collate (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 

int
fcompare(const void *xfile1, const void *xfile2)
{
    const Char *const *file1 = xfile1, *const *file2 = xfile2;

    return collate(*file1, *file2);
}