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
typedef  scalar_t__ sbits32 ;
typedef  int float32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeHex_bits16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeHex_bits8 (int,int /*<<< orphan*/ *) ; 

void writeHex_float32( float32 a, FILE *stream )
{

    fputc( ( ( (sbits32) a ) < 0 ) ? '8' : '0', stream );
    writeHex_bits8( a>>23, stream );
    fputc( '.', stream );
    writeHex_bits8( ( a>>16 ) & 0x7F, stream );
    writeHex_bits16( a, stream );

}