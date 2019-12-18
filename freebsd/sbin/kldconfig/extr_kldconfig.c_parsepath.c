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
struct pathhead {int dummy; } ;
struct pathentry {int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct pathhead*,struct pathentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addpath (struct pathhead*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 struct pathentry* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
parsepath(struct pathhead *pathq, char *path, int uniq)
{
	char *p;
	struct pathentry *pe;
	
	while ((p = strsep(&path, ";")) != NULL)
		if (!uniq) {
			if (((pe = malloc(sizeof(*pe))) == NULL) ||
			    ((pe->path = strdup(p)) == NULL)) {
				errno = ENOMEM;
				err(1, "allocating path element");
			}
			TAILQ_INSERT_TAIL(pathq, pe, next);
		} else {
			addpath(pathq, p, 1, 0);
		}
}