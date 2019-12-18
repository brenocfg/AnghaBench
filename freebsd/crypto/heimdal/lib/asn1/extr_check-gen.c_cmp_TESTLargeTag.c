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
typedef  int /*<<< orphan*/  TESTLargeTag ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bar ; 
 int /*<<< orphan*/  foo ; 

__attribute__((used)) static int
cmp_TESTLargeTag (void *a, void *b)
{
    TESTLargeTag *aa = a;
    TESTLargeTag *ab = b;

    COMPARE_INTEGER(aa,ab,foo);
    COMPARE_INTEGER(aa,ab,bar);
    return 0;
}