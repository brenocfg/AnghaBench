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
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote_c_style (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void write_name_quoted(const char *name, FILE *fp, int terminator)
{
	if (terminator) {
		quote_c_style(name, NULL, fp, 0);
	} else {
		fputs(name, fp);
	}
	fputc(terminator, fp);
}