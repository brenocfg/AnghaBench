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
typedef  int /*<<< orphan*/  heim_bmp_string ;

/* Variables and functions */
 int der_heim_bmp_string_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cmp_bmp_string (void *a, void *b)
{
    heim_bmp_string *oa = (heim_bmp_string *)a;
    heim_bmp_string *ob = (heim_bmp_string *)b;

    return der_heim_bmp_string_cmp(oa, ob);
}