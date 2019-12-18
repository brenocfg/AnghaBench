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
 int napic ; 
 int nbus ; 
 int ncpu ; 
 int nintr ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
MPConfigDefault( int featureByte )
{
    printf( "  MP default config type: %d\n\n", featureByte );
    switch ( featureByte ) {
    case 1:
	printf( "   bus: ISA, APIC: 82489DX\n" );
	break;
    case 2:
	printf( "   bus: EISA, APIC: 82489DX\n" );
	break;
    case 3:
	printf( "   bus: EISA, APIC: 82489DX\n" );
	break;
    case 4:
	printf( "   bus: MCA, APIC: 82489DX\n" );
	break;
    case 5:
	printf( "   bus: ISA+PCI, APIC: Integrated\n" );
	break;
    case 6:
	printf( "   bus: EISA+PCI, APIC: Integrated\n" );
	break;
    case 7:
	printf( "   bus: MCA+PCI, APIC: Integrated\n" );
	break;
    default:
	printf( "   future type\n" );
	break;
    }

    switch ( featureByte ) {
    case 1:
    case 2:
    case 3:
    case 4:
	nbus = 1;
	break;
    case 5:
    case 6:
    case 7:
	nbus = 2;
	break;
    default:
	printf( "   future type\n" );
	break;
    }

    ncpu = 2;
    napic = 1;
    nintr = 16;
}