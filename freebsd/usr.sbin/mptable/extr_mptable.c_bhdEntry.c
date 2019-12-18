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
typedef  TYPE_1__* bhd_entry_ptr ;
struct TYPE_3__ {int bus_id; int bus_info; int parent_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
bhdEntry( bhd_entry_ptr entry )
{

    printf( "--\nBus Hierarchy\n" );
    printf( " bus ID: %d", entry->bus_id );
    printf( " bus info: 0x%02x", entry->bus_info );
    printf( " parent bus ID: %d\n", entry->parent_bus );
}