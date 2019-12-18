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
struct roff_meta {scalar_t__ macroset; TYPE_1__* first; } ;
struct mparse {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 scalar_t__ MACROSET_MDOC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  mparse_readfd (struct mparse*,int,char const*) ; 
 struct roff_meta* mparse_result (struct mparse*) ; 
 int /*<<< orphan*/  pman (int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  pmdoc (int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
pmandoc(struct mparse *mp, int fd, const char *fn, int list)
{
	struct roff_meta	*meta;
	int		 line, col;

	mparse_readfd(mp, fd, fn);
	close(fd);
	meta = mparse_result(mp);
	line = 1;
	col = 0;

	if (meta->macroset == MACROSET_MDOC)
		pmdoc(meta->first->child, &line, &col, list);
	else
		pman(meta->first->child, &line, &col, list);

	if ( ! list)
		putchar('\n');
}