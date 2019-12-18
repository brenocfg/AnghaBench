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
struct strbuf {char* buf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* GIT_COLOR_RESET ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 

void color_print_strbuf(FILE *fp, const char *color, const struct strbuf *sb)
{
	if (*color)
		fprintf(fp, "%s", color);
	fprintf(fp, "%s", sb->buf);
	if (*color)
		fprintf(fp, "%s", GIT_COLOR_RESET);
}