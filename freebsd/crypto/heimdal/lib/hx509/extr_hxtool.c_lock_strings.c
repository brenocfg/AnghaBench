#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_lock ;
struct TYPE_3__ {int num_strings; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ getarg_strings ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int) ; 
 int hx509_lock_command_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lock_strings(hx509_lock lock, getarg_strings *pass)
{
    int i;
    for (i = 0; i < pass->num_strings; i++) {
	int ret = hx509_lock_command_string(lock, pass->strings[i]);
	if (ret)
	    errx(1, "hx509_lock_command_string: %s: %d",
		 pass->strings[i], ret);
    }
}