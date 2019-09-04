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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* GIT_COLOR_RESET ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int color_vfprintf(FILE *fp, const char *color, const char *fmt,
		va_list args, const char *trail)
{
	int r = 0;

	if (*color)
		r += fprintf(fp, "%s", color);
	r += vfprintf(fp, fmt, args);
	if (*color)
		r += fprintf(fp, "%s", GIT_COLOR_RESET);
	if (trail)
		r += fprintf(fp, "%s", trail);
	return r;
}