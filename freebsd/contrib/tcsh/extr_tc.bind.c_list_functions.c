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
struct KeyFuncs {int /*<<< orphan*/  desc; scalar_t__ name; } ;

/* Variables and functions */
 struct KeyFuncs* FuncNames ; 
 int /*<<< orphan*/  xprintf (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
list_functions(void)
{
    struct KeyFuncs *fp;

    for (fp = FuncNames; fp->name; fp++) {
	xprintf("%s\n          %s\n", fp->name, fp->desc);
    }
}