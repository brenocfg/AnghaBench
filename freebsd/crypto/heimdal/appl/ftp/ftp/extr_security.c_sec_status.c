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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ buffer_size ; 
 int /*<<< orphan*/  command_prot ; 
 int /*<<< orphan*/  data_prot ; 
 char* level_to_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* mech ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sec_complete ; 

void
sec_status(void)
{
    if(sec_complete){
	printf("Using %s for authentication.\n", mech->name);
	printf("Using %s command channel.\n", level_to_name(command_prot));
	printf("Using %s data channel.\n", level_to_name(data_prot));
	if(buffer_size > 0)
	    printf("Protection buffer size: %lu.\n",
		   (unsigned long)buffer_size);
    }else{
	printf("Not using any security mechanism.\n");
    }
}