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
struct local_zones {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  local_zones_add_RR (struct local_zones*,char*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
perform_data_add(RES* ssl, struct local_zones* zones, char* arg)
{
	if(!local_zones_add_RR(zones, arg)) {
		ssl_printf(ssl,"error in syntax or out of memory, %s\n", arg);
		return 0;
	}
	return 1;
}