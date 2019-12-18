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
struct mtree_fileinfo {scalar_t__ line; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mtree_fileinfo*,int /*<<< orphan*/ ) ; 
 struct mtree_fileinfo* emalloc (int) ; 
 void* estrdup (char const*) ; 
 int /*<<< orphan*/  free (struct mtree_fileinfo*) ; 
 int /*<<< orphan*/  mtree_fileinfo ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
mtree_file_push(const char *name, FILE *fp)
{
	struct mtree_fileinfo *fi;

	fi = emalloc(sizeof(*fi));
	if (strcmp(name, "-") == 0)
		fi->name = estrdup("(stdin)");
	else
		fi->name = estrdup(name);
	if (fi->name == NULL) {
		free(fi);
		return (ENOMEM);
	}

	fi->fp = fp;
	fi->line = 0;

	SLIST_INSERT_HEAD(&mtree_fileinfo, fi, next);
	return (0);
}