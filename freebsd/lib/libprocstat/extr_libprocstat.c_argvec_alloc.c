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
struct argvec {size_t bufsize; int argc; struct argvec* buf; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct argvec*) ; 
 void* malloc (int) ; 

__attribute__((used)) static struct argvec *
argvec_alloc(size_t bufsize)
{
	struct argvec *av;

	av = malloc(sizeof(*av));
	if (av == NULL)
		return (NULL);
	av->bufsize = bufsize;
	av->buf = malloc(av->bufsize);
	if (av->buf == NULL) {
		free(av);
		return (NULL);
	}
	av->argc = 32;
	av->argv = malloc(sizeof(char *) * av->argc);
	if (av->argv == NULL) {
		free(av->buf);
		free(av);
		return (NULL);
	}
	return av;
}