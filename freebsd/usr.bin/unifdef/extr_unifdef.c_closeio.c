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
 scalar_t__ EOF ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/ * input ; 
 int /*<<< orphan*/ * output ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ symdepth ; 
 int /*<<< orphan*/  zerosyms ; 

__attribute__((used)) static void
closeio(void)
{
	/* Tidy up after findsym(). */
	if (symdepth && !zerosyms)
		printf("\n");
	if (output != NULL && (ferror(output) || fclose(output) == EOF))
			err(2, "%s: can't write to output", filename);
	fclose(input);
}