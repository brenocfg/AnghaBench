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
typedef  int /*<<< orphan*/ **** wint_t ;

/* Variables and functions */
 int /*<<< orphan*/  el_free (int /*<<< orphan*/ ******) ; 

__attribute__((used)) static void
terminal_free_buffer(wint_t ***bp)
{
	wint_t **b;
	wint_t **bufp;

	if (*bp == NULL)
		return;

	b = *bp;
	*bp = NULL;

	for (bufp = b; *bufp != NULL; bufp++)
		el_free(*bufp);
	el_free(b);
}