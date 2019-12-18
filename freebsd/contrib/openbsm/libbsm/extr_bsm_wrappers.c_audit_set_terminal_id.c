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
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ au_tid_t ;

/* Variables and functions */
 int audit_set_terminal_host (int /*<<< orphan*/ *) ; 
 int audit_set_terminal_port (int /*<<< orphan*/ *) ; 
 int kAUBadParamErr ; 
 int kAUNoErr ; 

int
audit_set_terminal_id(au_tid_t *tid)
{
	dev_t port;
	int ret;

	if (tid == NULL)
		return (kAUBadParamErr);
	if ((ret = audit_set_terminal_port(&port)) != kAUNoErr)
		return (ret);
	tid->port = port;
	return (audit_set_terminal_host(&tid->machine));
}