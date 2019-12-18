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
struct mpt_personality {int id; int (* load ) (struct mpt_personality*) ;int (* unload ) (struct mpt_personality*) ;} ;
typedef  int /*<<< orphan*/  mpt_load_handler_t ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  MOD_LOAD 131 
#define  MOD_QUIESCE 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int MPT_MAX_PERSONALITIES ; 
 int /*<<< orphan*/ ** MPT_PERS_FIRST_HANDLER (struct mpt_personality*) ; 
 int /*<<< orphan*/ ** MPT_PERS_LAST_HANDLER (struct mpt_personality*) ; 
 struct mpt_personality mpt_default_personality ; 
 struct mpt_personality** mpt_personalities ; 
 int stub1 (struct mpt_personality*) ; 
 int stub2 (struct mpt_personality*) ; 

int
mpt_modevent(module_t mod, int type, void *data)
{
	struct mpt_personality *pers;
	int error;

	pers = (struct mpt_personality *)data;

	error = 0;
	switch (type) {
	case MOD_LOAD:
	{
		mpt_load_handler_t **def_handler;
		mpt_load_handler_t **pers_handler;
		int i;

		for (i = 0; i < MPT_MAX_PERSONALITIES; i++) {
			if (mpt_personalities[i] == NULL)
				break;
		}
		if (i >= MPT_MAX_PERSONALITIES) {
			error = ENOMEM;
			break;
		}
		pers->id = i;
		mpt_personalities[i] = pers;

		/* Install standard/noop handlers for any NULL entries. */
		def_handler = MPT_PERS_FIRST_HANDLER(&mpt_default_personality);
		pers_handler = MPT_PERS_FIRST_HANDLER(pers);
		while (pers_handler <= MPT_PERS_LAST_HANDLER(pers)) {
			if (*pers_handler == NULL)
				*pers_handler = *def_handler;
			pers_handler++;
			def_handler++;
		}
		
		error = (pers->load(pers));
		if (error != 0)
			mpt_personalities[i] = NULL;
		break;
	}
	case MOD_SHUTDOWN:
		break;
	case MOD_QUIESCE:
		break;
	case MOD_UNLOAD:
		error = pers->unload(pers);
		mpt_personalities[pers->id] = NULL;
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}