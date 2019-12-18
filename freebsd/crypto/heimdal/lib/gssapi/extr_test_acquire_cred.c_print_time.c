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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_INDEFINITE ; 
 char* ctime (scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_time(OM_uint32 time_rec)
{
    if (time_rec == GSS_C_INDEFINITE) {
	printf("cred never expire\n");
    } else {
	time_t t = time_rec + time(NULL);
	printf("expiration time: %s", ctime(&t));
    }
}