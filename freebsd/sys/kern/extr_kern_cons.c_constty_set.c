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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_TTYCONS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * consbuf ; 
 int /*<<< orphan*/  conscallout ; 
 int /*<<< orphan*/  consmsgbuf ; 
 int consmsgbuf_size ; 
 struct tty* constty ; 
 int /*<<< orphan*/  constty_timeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
constty_set(struct tty *tp)
{
	int size;

	KASSERT(tp != NULL, ("constty_set: NULL tp"));
	if (consbuf == NULL) {
		size = consmsgbuf_size;
		consbuf = malloc(size, M_TTYCONS, M_WAITOK);
		msgbuf_init(&consmsgbuf, consbuf, size);
		callout_init(&conscallout, 0);
	}
	constty = tp;
	constty_timeout(NULL);
}