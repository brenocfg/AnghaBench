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
 int /*<<< orphan*/ * codefile ; 
 int /*<<< orphan*/  one_code_file ; 
 int /*<<< orphan*/ * templatefile ; 

__attribute__((used)) static FILE *
get_code_file(void)
{
    if (!one_code_file)
	return templatefile;
    return codefile;
}