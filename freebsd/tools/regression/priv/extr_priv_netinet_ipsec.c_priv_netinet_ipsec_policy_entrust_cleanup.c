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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * entrustbuf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int sd ; 

void
priv_netinet_ipsec_policy_entrust_cleanup(int asroot, int injail,
    struct test *test)
{

	if (entrustbuf != NULL) {
		free(entrustbuf);
		entrustbuf = NULL;
	}
	if (sd >= 0) {
		close(sd);
		sd = -1;
	}
}