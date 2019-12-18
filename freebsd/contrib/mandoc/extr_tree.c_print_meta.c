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
struct roff_meta {char* title; char* name; char* msec; char* vol; char* arch; char* os; char* date; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
print_meta(const struct roff_meta *meta)
{
	if (meta->title != NULL)
		printf("title = \"%s\"\n", meta->title);
	if (meta->name != NULL)
		printf("name  = \"%s\"\n", meta->name);
	if (meta->msec != NULL)
		printf("sec   = \"%s\"\n", meta->msec);
	if (meta->vol != NULL)
		printf("vol   = \"%s\"\n", meta->vol);
	if (meta->arch != NULL)
		printf("arch  = \"%s\"\n", meta->arch);
	if (meta->os != NULL)
		printf("os    = \"%s\"\n", meta->os);
	if (meta->date != NULL)
		printf("date  = \"%s\"\n", meta->date);
}