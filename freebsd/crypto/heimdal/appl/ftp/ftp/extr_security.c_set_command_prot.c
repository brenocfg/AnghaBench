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
typedef  enum protection_level { ____Placeholder_protection_level } protection_level ;

/* Variables and functions */
 int COMPLETE ; 
 int command (char*) ; 
 int command_prot ; 
 int /*<<< orphan*/  printf (char*) ; 
 int prot_clear ; 
 int prot_invalid ; 

enum protection_level
set_command_prot(enum protection_level level)
{
    int ret;
    enum protection_level old = command_prot;
    if(level != command_prot && level == prot_clear) {
	ret = command("CCC");
	if(ret != COMPLETE) {
	    printf("Failed to clear command channel.\n");
	    return prot_invalid;
	}
    }
    command_prot = level;
    return old;
}