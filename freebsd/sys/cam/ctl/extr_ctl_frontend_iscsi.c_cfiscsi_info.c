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
struct sbuf {int dummy; } ;
struct cfiscsi_target {int /*<<< orphan*/  ct_state; } ;

/* Variables and functions */
 int sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfiscsi_info(void *arg, struct sbuf *sb)
{
	struct cfiscsi_target *ct = (struct cfiscsi_target *)arg;
	int retval;

	retval = sbuf_printf(sb, "\t<cfiscsi_state>%d</cfiscsi_state>\n",
	    ct->ct_state);
	return (retval);
}