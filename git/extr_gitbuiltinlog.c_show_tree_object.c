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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ S_ISDIR (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 

__attribute__((used)) static int show_tree_object(const struct object_id *oid,
		struct strbuf *base,
		const char *pathname, unsigned mode, int stage, void *context)
{
	FILE *file = context;
	fprintf(file, "%s%s\n", pathname, S_ISDIR(mode) ? "/" : "");
	return 0;
}