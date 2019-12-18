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
typedef  TYPE_1__* proc_entry_ptr ;
struct TYPE_3__ {int apic_id; int apic_version; int cpu_flags; int cpu_signature; int feature_flags; } ;

/* Variables and functions */
 int PROCENTRY_FLAG_BP ; 
 int PROCENTRY_FLAG_EN ; 
 int /*<<< orphan*/  ncpu ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
processorEntry( proc_entry_ptr entry )
{

    /* count it */
    ++ncpu;

    printf( "\t\t%2d", entry->apic_id );
    printf( "\t 0x%2x", entry->apic_version );

    printf( "\t %s, %s",
            (entry->cpu_flags & PROCENTRY_FLAG_BP) ? "BSP" : "AP",
            (entry->cpu_flags & PROCENTRY_FLAG_EN) ? "usable" : "unusable" );

    printf( "\t %d\t %d\t %d",
            (entry->cpu_signature >> 8) & 0x0f,
            (entry->cpu_signature >> 4) & 0x0f,
            entry->cpu_signature & 0x0f );

    printf( "\t 0x%04x\n", entry->feature_flags );
}