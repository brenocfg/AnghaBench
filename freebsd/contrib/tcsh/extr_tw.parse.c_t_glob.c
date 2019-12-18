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
typedef  int /*<<< orphan*/  jmp_buf_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int NeedsRedraw ; 
 int blklen (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cleanup_pop_mark (size_t) ; 
 size_t cleanup_push_mark () ; 
 int /*<<< orphan*/  executable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** globall (int /*<<< orphan*/ **,int) ; 
 scalar_t__ haderr ; 
 int /*<<< orphan*/  resexit (int /*<<< orphan*/ ) ; 
 scalar_t__ setexit () ; 
 int tglob (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
t_glob(Char ***v, int cmd)
{
    jmp_buf_t osetexit;
    int gflag;

    if (**v == 0)
	return (0);
    gflag = tglob(*v);
    if (gflag) {
	size_t omark;

	getexit(osetexit);	/* make sure to come back here */
	omark = cleanup_push_mark();
	if (setexit() == 0)
	    *v = globall(*v, gflag);
	cleanup_pop_mark(omark);
	resexit(osetexit);
	if (haderr) {
	    haderr = 0;
	    NeedsRedraw = 1;
	    return (-1);
	}
	if (*v == 0)
	    return (0);
    }
    else
	return (0);

    if (cmd) {
	Char **av = *v, *p;
	int fwd, i;

	for (i = 0, fwd = 0; av[i] != NULL; i++) 
	    if (!executable(NULL, av[i], 0)) {
		fwd++;		
		p = av[i];
		av[i] = NULL;
		xfree(p);
	    }
	    else if (fwd) 
		av[i - fwd] = av[i];

	if (fwd)
	    av[i - fwd] = av[i];
    }

    return blklen(*v);
}