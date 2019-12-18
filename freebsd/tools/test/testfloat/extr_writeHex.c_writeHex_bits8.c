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
typedef  int bits8 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void writeHex_bits8( bits8 a, FILE *stream )
{
    int digit;

    digit = ( a>>4 ) & 0xF;
    if ( 9 < digit ) digit += 'A' - ( '0' + 10 );
    fputc( '0' + digit, stream );
    digit = a & 0xF;
    if ( 9 < digit ) digit += 'A' - ( '0' + 10 );
    fputc( '0' + digit, stream );

}