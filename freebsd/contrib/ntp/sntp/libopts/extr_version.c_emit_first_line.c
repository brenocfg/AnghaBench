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
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_first_line(
    FILE * fp, char const * alt1, char const * alt2, char const * alt3)
{
    char const * p = (alt1 != NULL) ? alt1 : ((alt2 != NULL) ? alt2 : alt3);
    char const * e;
    if (p == NULL)
        return;
    e = strchr(p, NL);
    if (e == NULL)
        fputs(p, fp);
    else
        fwrite(p, 1, (e - p), fp);
    fputc(NL, fp);
}