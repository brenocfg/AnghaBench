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
 void* FALSE ; 
 void* TRUE ; 
 void* debug ; 
 int /*<<< orphan*/  srec2bin (int,char**,void*) ; 
 void* verbose ; 

int main(int argc, char *argv[])
{
    debug = TRUE;
    debug = FALSE;
    verbose = FALSE;
    srec2bin(argc,argv,verbose);
    return 0;
}