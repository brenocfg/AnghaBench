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
typedef  int uintmax_t ;
typedef  TYPE_1__* sas_entry_ptr ;
struct TYPE_3__ {int bus_id; int address_type; scalar_t__ address_length; scalar_t__ address_base; } ;

/* Variables and functions */
#define  SASENTRY_TYPE_IO 130 
#define  SASENTRY_TYPE_MEMORY 129 
#define  SASENTRY_TYPE_PREFETCH 128 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
sasEntry( sas_entry_ptr entry )
{

    printf( "--\nSystem Address Space\n");
    printf( " bus ID: %d", entry->bus_id );
    printf( " address type: " );
    switch ( entry->address_type ) {
    case SASENTRY_TYPE_IO:
	printf( "I/O address\n" );
	break;
    case SASENTRY_TYPE_MEMORY:
	printf( "memory address\n" );
	break;
    case SASENTRY_TYPE_PREFETCH:
	printf( "prefetch address\n" );
	break;
    default:
	printf( "UNKNOWN type\n" );
	break;
    }

    printf( " address base: 0x%jx\n", (uintmax_t)entry->address_base );
    printf( " address range: 0x%jx\n", (uintmax_t)entry->address_length );
}