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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  if_clone_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stf_clone_create ; 
 int /*<<< orphan*/  stf_clone_destroy ; 
 int /*<<< orphan*/  stf_clone_match ; 
 int /*<<< orphan*/  stf_cloner ; 
 int /*<<< orphan*/  stfname ; 

__attribute__((used)) static int
stfmodevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		stf_cloner = if_clone_advanced(stfname, 0, stf_clone_match,
		    stf_clone_create, stf_clone_destroy);
		break;
	case MOD_UNLOAD:
		if_clone_detach(stf_cloner);
		break;
	default:
		return (EOPNOTSUPP);
	}

	return (0);
}