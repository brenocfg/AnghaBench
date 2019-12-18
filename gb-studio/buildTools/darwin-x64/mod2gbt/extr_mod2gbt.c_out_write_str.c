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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ output_asm ; 
 int /*<<< orphan*/  output_file ; 

void out_write_str(const char * c_str, const char * asm_str)
{
    fprintf(output_file,output_asm ? asm_str : c_str);
}