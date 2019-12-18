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
struct csock_buf {int /*<<< orphan*/  path; int /*<<< orphan*/  mesg; } ;

/* Variables and functions */
 struct csock_buf* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csock_bufs ; 
 int /*<<< orphan*/  csock_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct csock_buf*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
ng_idle(void)
{
	struct csock_buf *b;

	/* execute waiting csock_bufs */
	while ((b = STAILQ_FIRST(&csock_bufs)) != NULL) {
		STAILQ_REMOVE_HEAD(&csock_bufs, link);
		csock_handle(b->mesg, b->path);
		free(b);
	}
}