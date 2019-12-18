#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ l; } ;
typedef  TYPE_1__ kstring_t ;

/* Variables and functions */
 int /*<<< orphan*/  check (char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kputw (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void test_kputw(kstring_t *ks, int n)
{
	char buf[16];

	ks->l = 0;
	kputw(n, ks);

	sprintf(buf, "%d", n);
	check("kputw()", ks, buf);
}