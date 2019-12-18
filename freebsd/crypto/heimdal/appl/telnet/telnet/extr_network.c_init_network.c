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
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netibufsize ; 
 int /*<<< orphan*/  netiring ; 
 int /*<<< orphan*/  netobufsize ; 
 int /*<<< orphan*/  netoring ; 
 int ring_init (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
init_network(void)
{
    void *obuf, *ibuf;

    if ((obuf = malloc(netobufsize)) == NULL)
	exit(1);
    if ((ibuf = malloc(netibufsize)) == NULL)
	exit(1);

    if (ring_init(&netoring, obuf, netobufsize) != 1) {
	exit(1);
    }
    if (ring_init(&netiring, ibuf, netibufsize) != 1) {
	exit(1);
    }
    NetTrace = stdout;
}