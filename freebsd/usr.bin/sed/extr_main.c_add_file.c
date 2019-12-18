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
struct s_flist {char* fname; struct s_flist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 struct s_flist** fl_nextp ; 
 struct s_flist* malloc (int) ; 

__attribute__((used)) static void
add_file(char *s)
{
	struct s_flist *fp;

	if ((fp = malloc(sizeof(struct s_flist))) == NULL)
		err(1, "malloc");
	fp->next = NULL;
	*fl_nextp = fp;
	fp->fname = s;
	fl_nextp = &fp->next;
}