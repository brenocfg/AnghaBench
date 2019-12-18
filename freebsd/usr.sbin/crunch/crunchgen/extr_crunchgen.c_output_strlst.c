#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* str; struct TYPE_3__* next; } ;
typedef  TYPE_1__ strlst_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strlen (char*) ; 

void
output_strlst(FILE *outf, strlst_t *lst)
{
	for (; lst != NULL; lst = lst->next)
		if ( strlen(lst->str) )
			fprintf(outf, " %s", lst->str);
	fprintf(outf, "\n");
}