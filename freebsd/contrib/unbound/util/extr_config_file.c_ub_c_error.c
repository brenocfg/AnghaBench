#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* filename; int line; int /*<<< orphan*/  errors; } ;

/* Variables and functions */
 TYPE_1__* cfg_parser ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char const*) ; 
 int /*<<< orphan*/  stderr ; 

void ub_c_error(const char *str)
{
	cfg_parser->errors++;
	fprintf(stderr, "%s:%d: error: %s\n", cfg_parser->filename,
		cfg_parser->line, str);
}