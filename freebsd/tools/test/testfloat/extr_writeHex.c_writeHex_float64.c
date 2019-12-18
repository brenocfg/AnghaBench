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
struct TYPE_3__ {int high; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ float64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeHex_bits12 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeHex_bits32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeHex_bits8 (int,int /*<<< orphan*/ *) ; 

void writeHex_float64( float64 a, FILE *stream )
{

    writeHex_bits12( a.high>>20, stream );
    fputc( '.', stream );
    writeHex_bits12( a.high>>8, stream );
    writeHex_bits8( a.high, stream );
    writeHex_bits32( a.low, stream );

}