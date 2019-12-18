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
struct mc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UML_MCONSOLE_HELPTEXT ; 
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mconsole_help(struct mc_request *req)
{
	mconsole_reply(req, UML_MCONSOLE_HELPTEXT, 0, 0);
}