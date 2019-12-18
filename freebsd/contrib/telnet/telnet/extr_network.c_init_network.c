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
 int /*<<< orphan*/  NetTrace ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  netibuf ; 
 int /*<<< orphan*/  netiring ; 
 int /*<<< orphan*/  netobuf ; 
 int /*<<< orphan*/  netoring ; 
 int ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

void
init_network(void)
{
    if (ring_init(&netoring, netobuf, sizeof netobuf) != 1) {
	exit(1);
    }
    if (ring_init(&netiring, netibuf, sizeof netibuf) != 1) {
	exit(1);
    }
    NetTrace = stdout;
}