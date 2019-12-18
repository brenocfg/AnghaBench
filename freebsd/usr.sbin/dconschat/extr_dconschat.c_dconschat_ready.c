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
struct dcons_state {int flags; } ;
typedef  int /*<<< orphan*/  oldreason ;

/* Variables and functions */
 int F_READY ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
dconschat_ready(struct dcons_state *dc, int ready, char *reason)
{
	static char oldreason[64] = "";
	int old;

	old = (dc->flags & F_READY) ? 1 : 0;

	if (ready) {
		dc->flags |= F_READY;
		if (ready != old)
			printf("[dcons connected]\r\n");
		oldreason[0] = 0;
	} else {
		dc->flags &= ~F_READY;
		if (strncmp(oldreason, reason, sizeof(oldreason)) != 0) {
			printf("[dcons disconnected (%s)]\r\n", reason);
			strlcpy(oldreason, reason, sizeof(oldreason));
		}
	}
}