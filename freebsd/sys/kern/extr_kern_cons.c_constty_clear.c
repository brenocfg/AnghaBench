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

/* Variables and functions */
 int /*<<< orphan*/  M_TTYCONS ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnputc (int) ; 
 int /*<<< orphan*/ * consbuf ; 
 int /*<<< orphan*/  conscallout ; 
 int /*<<< orphan*/  consmsgbuf ; 
 int /*<<< orphan*/ * constty ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int msgbuf_getchar (int /*<<< orphan*/ *) ; 

void
constty_clear(void)
{
	int c;

	constty = NULL;
	if (consbuf == NULL)
		return;
	callout_stop(&conscallout);
	while ((c = msgbuf_getchar(&consmsgbuf)) != -1)
		cnputc(c);
	free(consbuf, M_TTYCONS);
	consbuf = NULL;
}