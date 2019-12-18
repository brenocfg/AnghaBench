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
struct TYPE_3__ {struct TYPE_3__* description; struct TYPE_3__* term_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ len_termdata ; 
 TYPE_1__* ptr_termdata ; 
 size_t use_termdata ; 

__attribute__((used)) static void
free_termdata(void)
{
    if (ptr_termdata != 0) {
	while (use_termdata != 0) {
	    --use_termdata;
	    free(ptr_termdata[use_termdata].term_name);
	    free(ptr_termdata[use_termdata].description);
	}
	free(ptr_termdata);
	ptr_termdata = 0;
    }
    use_termdata = 0;
    len_termdata = 0;
}