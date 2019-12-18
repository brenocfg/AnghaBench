#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  TYPE_1__* mpfps_t ;
struct TYPE_4__ {int length; int spec_rev; int checksum; int mpfb2; scalar_t__ mpfb5; scalar_t__ mpfb4; scalar_t__ mpfb3; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int MPFB2_IMCR_PRESENT ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* mapEntry (int,int) ; 
 int /*<<< orphan*/  pnstr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
MPFloatingPointer( u_int32_t paddr, int where, mpfps_t* mpfpsp )
{
    mpfps_t mpfps;
	
    /* map in mpfps structure*/
    *mpfpsp = mpfps = mapEntry( paddr, sizeof( *mpfps ) );

    /* show its contents */
    printf( "MP Floating Pointer Structure:\n\n" );

    printf( "  location:\t\t\t" );
    switch ( where )
    {
    case 1:
	printf( "EBDA\n" );
	break;
    case 2:
	printf( "BIOS base memory\n" );
	break;
    case 3:
	printf( "DEFAULT base memory (639K)\n" );
	break;
    case 4:
	printf( "BIOS\n" );
	break;
    case 5:
	printf( "Extended BIOS\n" );
	break;

    case 0:
	printf( "NOT found!\n" );
	exit( 1 );
    default:
	printf( "BOGUS!\n" );
	exit( 1 );
    }
    printf( "  physical address:\t\t0x%08x\n", paddr );

    printf( "  signature:\t\t\t'" );
    pnstr( mpfps->signature, 4 );
    printf( "'\n" );

    printf( "  length:\t\t\t%d bytes\n", mpfps->length * 16 );
    printf( "  version:\t\t\t1.%1d\n", mpfps->spec_rev );
    printf( "  checksum:\t\t\t0x%02x\n", mpfps->checksum );

    /* bits 0:6 are RESERVED */
    if ( mpfps->mpfb2 & 0x7f ) {
        printf( " warning, MP feature byte 2: 0x%02x\n", mpfps->mpfb2 );
    }

    /* bit 7 is IMCRP */
    printf( "  mode:\t\t\t\t%s\n", (mpfps->mpfb2 & MPFB2_IMCR_PRESENT) ?
            "PIC" : "Virtual Wire" );

    /* MP feature bytes 3-5 are expected to be ZERO */
    if ( mpfps->mpfb3 )
        printf( " warning, MP feature byte 3 NONZERO!\n" );
    if ( mpfps->mpfb4 )
        printf( " warning, MP feature byte 4 NONZERO!\n" );
    if ( mpfps->mpfb5 )
        printf( " warning, MP feature byte 5 NONZERO!\n" );
}