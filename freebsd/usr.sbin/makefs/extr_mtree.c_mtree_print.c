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
struct mtree_fileinfo {char* name; int line; } ;

/* Variables and functions */
 struct mtree_fileinfo* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  mtree_fileinfo ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mtree_print(const char *msgtype, const char *fmt, va_list ap)
{
	struct mtree_fileinfo *fi;

	if (msgtype != NULL) {
		fi = SLIST_FIRST(&mtree_fileinfo);
		if (fi != NULL)
			fprintf(stderr, "%s:%u: ", fi->name, fi->line);
		fprintf(stderr, "%s: ", msgtype);
	}
	vfprintf(stderr, fmt, ap);
}