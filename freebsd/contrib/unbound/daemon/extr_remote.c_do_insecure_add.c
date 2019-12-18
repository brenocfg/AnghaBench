#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ anchors; } ;
struct worker {TYPE_1__ env; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  anchors_add_insecure (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
do_insecure_add(RES* ssl, struct worker* worker, char* arg)
{
	size_t nmlen;
	int nmlabs;
	uint8_t* nm = NULL;
	if(!parse_arg_name(ssl, arg, &nm, &nmlen, &nmlabs))
		return;
	if(worker->env.anchors) {
		if(!anchors_add_insecure(worker->env.anchors,
			LDNS_RR_CLASS_IN, nm)) {
			(void)ssl_printf(ssl, "error out of memory\n");
			free(nm);
			return;
		}
	}
	free(nm);
	send_ok(ssl);
}