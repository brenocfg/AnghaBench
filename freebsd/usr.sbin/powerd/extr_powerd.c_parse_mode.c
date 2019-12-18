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
 int MODE_ADAPTIVE ; 
 int MODE_HIADAPTIVE ; 
 int MODE_MAX ; 
 int MODE_MIN ; 
 int /*<<< orphan*/  errx (int,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
parse_mode(char *arg, int *mode, int ch)
{

	if (strcmp(arg, "minimum") == 0 || strcmp(arg, "min") == 0)
		*mode = MODE_MIN;
	else if (strcmp(arg, "maximum") == 0 || strcmp(arg, "max") == 0)
		*mode = MODE_MAX;
	else if (strcmp(arg, "adaptive") == 0 || strcmp(arg, "adp") == 0)
		*mode = MODE_ADAPTIVE;
	else if (strcmp(arg, "hiadaptive") == 0 || strcmp(arg, "hadp") == 0)
		*mode = MODE_HIADAPTIVE;
	else
		errx(1, "bad option: -%c %s", (char)ch, optarg);
}