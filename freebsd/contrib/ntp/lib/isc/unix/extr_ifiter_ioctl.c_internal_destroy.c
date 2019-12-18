#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int socket; int socket6; int /*<<< orphan*/ * proc; int /*<<< orphan*/  bufsize6; int /*<<< orphan*/ * buf6; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
internal_destroy(isc_interfaceiter_t *iter) {
	(void) close(iter->socket);
#if defined(SIOCGLIFCONF) && defined(SIOCGLIFADDR)
	if (iter->socket6 != -1)
		(void) close(iter->socket6);
	if (iter->buf6 != NULL) {
		isc_mem_put(iter->mctx, iter->buf6, iter->bufsize6);
	}
#endif
#ifdef __linux
	if (iter->proc != NULL)
		fclose(iter->proc);
#endif
}