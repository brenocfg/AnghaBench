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
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ fputc (char,int /*<<< orphan*/ *) ; 
 TYPE_1__** info ; 
 int num_pack ; 
 char* pack_basename (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_pack_info_file(FILE *fp)
{
	int i;
	for (i = 0; i < num_pack; i++) {
		if (fprintf(fp, "P %s\n", pack_basename(info[i]->p)) < 0)
			return -1;
	}
	if (fputc('\n', fp) == EOF)
		return -1;
	return 0;
}