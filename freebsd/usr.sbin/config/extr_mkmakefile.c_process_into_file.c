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
 int BUFSIZ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ preprocess (char*,char*) ; 

__attribute__((used)) static void
process_into_file(char *line, FILE *ofp)
{
	char result[BUFSIZ];

	if (preprocess(line, result))
		fprintf(ofp, "\"%s\\0\"\n", result);
}