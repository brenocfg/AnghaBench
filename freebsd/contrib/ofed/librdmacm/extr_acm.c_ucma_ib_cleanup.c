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
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  shutdown (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sock ; 

void ucma_ib_cleanup(void)
{
	if (sock >= 0) {
		shutdown(sock, SHUT_RDWR);
		close(sock);
	}
}