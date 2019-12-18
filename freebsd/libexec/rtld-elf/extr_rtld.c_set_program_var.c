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

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,char const*,void const**,void const*) ; 
 void** get_program_var_addr (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_program_var(const char *name, const void *value)
{
    const void **addr;

    if ((addr = get_program_var_addr(name, NULL)) != NULL) {
	dbg("\"%s\": *%p <-- %p", name, addr, value);
	*addr = value;
    }
}