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
 scalar_t__ defundef () ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char const* filename ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ incomment ; 
 int /*<<< orphan*/ * input ; 
 scalar_t__ linenum ; 

__attribute__((used)) static void
defundefile(const char *fn)
{
	filename = fn;
	input = fopen(fn, "rb");
	if (input == NULL)
		err(2, "can't open %s", fn);
	linenum = 0;
	while (defundef())
		;
	if (ferror(input))
		err(2, "can't read %s", filename);
	else
		fclose(input);
	if (incomment)
		error("EOF in comment");
}