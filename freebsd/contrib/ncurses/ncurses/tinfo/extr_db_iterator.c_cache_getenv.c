#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* value; } ;
typedef  size_t DBDIRS ;

/* Variables and functions */
 size_t dbdLAST ; 
 TYPE_1__* my_vars ; 
 int /*<<< orphan*/  update_getenv (char const*,size_t) ; 

__attribute__((used)) static char *
cache_getenv(const char *name, DBDIRS which)
{
    char *result = 0;

    (void) update_getenv(name, which);
    if (which < dbdLAST) {
	result = my_vars[which].value;
    }
    return result;
}