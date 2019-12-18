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
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACTION_DEBUG (char*) ; 
 int /*<<< orphan*/  IPFW_ADD_OBJ_REWRITER (int,int /*<<< orphan*/ ) ; 
 int create_eaction_obj (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_eaction ; 
 int /*<<< orphan*/  default_eaction_typename ; 
 int /*<<< orphan*/  eaction_opcodes ; 

int
ipfw_eaction_init(struct ip_fw_chain *ch, int first)
{
	int error;

	error = create_eaction_obj(ch, default_eaction,
	    default_eaction_typename, NULL);
	if (error != 0)
		return (error);
	IPFW_ADD_OBJ_REWRITER(first, eaction_opcodes);
	EACTION_DEBUG("External actions support initialized");
	return (0);
}