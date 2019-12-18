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
 int /*<<< orphan*/  kputl (long,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 

void test_kputl(kstring_t *ks, long n)
{
	char buf[24];

	ks->l = 0;
	kputl(n, ks);

	sprintf(buf, "%ld", n);
	check("kputl()", ks, buf);
}