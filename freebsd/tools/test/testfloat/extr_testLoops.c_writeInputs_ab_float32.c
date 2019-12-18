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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  testCases_a_float32 ; 
 int /*<<< orphan*/  testCases_b_float32 ; 
 int /*<<< orphan*/  writeHex_float32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeInputs_ab_float32( void )
{

    writeHex_float32( testCases_a_float32, stdout );
    fputs( "  ", stdout );
    writeHex_float32( testCases_b_float32, stdout );

}