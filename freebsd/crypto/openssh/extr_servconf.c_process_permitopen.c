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
struct ssh {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_permitted_listens; int /*<<< orphan*/  permitted_listens; int /*<<< orphan*/  num_permitted_opens; int /*<<< orphan*/  permitted_opens; } ;
typedef  TYPE_1__ ServerOptions ;

/* Variables and functions */
 int /*<<< orphan*/  process_permitopen_list (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sPermitListen ; 
 int /*<<< orphan*/  sPermitOpen ; 

void
process_permitopen(struct ssh *ssh, ServerOptions *options)
{
	process_permitopen_list(ssh, sPermitOpen,
	    options->permitted_opens, options->num_permitted_opens);
	process_permitopen_list(ssh, sPermitListen,
	    options->permitted_listens,
	    options->num_permitted_listens);
}