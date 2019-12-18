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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
print_bt(FILE *f, int flag)
{
    if(flag == 0){
	fprintf(f, "/* For compatibility with various type definitions */\n");
	fprintf(f, "#ifndef __BIT_TYPES_DEFINED__\n");
	fprintf(f, "#define __BIT_TYPES_DEFINED__\n");
	fprintf(f, "\n");
    }
    return 1;
}