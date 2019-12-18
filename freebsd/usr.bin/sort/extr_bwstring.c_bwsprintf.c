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
struct TYPE_2__ {char* cstr; char* wstr; } ;
struct bwstring {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*,char const*) ; 

void
bwsprintf(FILE *f, struct bwstring *bws, const char *prefix, const char *suffix)
{

	if (MB_CUR_MAX == 1)
		fprintf(f, "%s%s%s", prefix, bws->data.cstr, suffix);
	else
		fprintf(f, "%s%S%s", prefix, bws->data.wstr, suffix);
}