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
struct input {int lno; void* path; void* fname; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct input*,int /*<<< orphan*/ ) ; 
 struct input* input ; 
 int /*<<< orphan*/  inputs ; 
 int /*<<< orphan*/  link ; 
 void* savestr (char const*) ; 
 struct input* xalloc (int) ; 

__attribute__((used)) static void
input_new(FILE *fp, const char *path, const char *fname)
{
	struct input *ip;

	ip = xalloc(sizeof(*ip));
	ip->fp = fp;
	ip->lno = 1;
	ip->fname = savestr(fname);
	ip->path = savestr(path);
	LIST_INSERT_HEAD(&inputs, ip, link);

	input = ip;
}