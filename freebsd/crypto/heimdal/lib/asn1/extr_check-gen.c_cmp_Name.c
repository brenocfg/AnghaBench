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
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  element ; 

__attribute__((used)) static int
cmp_Name (void *a, void *b)
{
    Name *aa = a;
    Name *ab = b;

    COMPARE_INTEGER(aa,ab,element);

    return 0;
}