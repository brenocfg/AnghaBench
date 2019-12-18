#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int (* read_op ) (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_handler ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
pcap_dispatch(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	return (p->read_op(p, cnt, callback, user));
}