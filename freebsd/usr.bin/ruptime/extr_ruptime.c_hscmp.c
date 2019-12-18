#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wd_hostname; } ;
struct TYPE_4__ {TYPE_1__ hs_wd; } ;

/* Variables and functions */
 TYPE_2__* HS (void const*) ; 
 int rflg ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hscmp(const void *a1, const void *a2)
{
	return (rflg *
	    strcmp(HS(a1)->hs_wd.wd_hostname, HS(a2)->hs_wd.wd_hostname));
}