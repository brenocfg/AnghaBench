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
struct submodule_update_strategy {int type; int /*<<< orphan*/  command; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
#define  SM_UPDATE_CHECKOUT 133 
#define  SM_UPDATE_COMMAND 132 
#define  SM_UPDATE_MERGE 131 
#define  SM_UPDATE_NONE 130 
#define  SM_UPDATE_REBASE 129 
#define  SM_UPDATE_UNSPECIFIED 128 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 char const* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

const char *submodule_strategy_to_string(const struct submodule_update_strategy *s)
{
	struct strbuf sb = STRBUF_INIT;
	switch (s->type) {
	case SM_UPDATE_CHECKOUT:
		return "checkout";
	case SM_UPDATE_MERGE:
		return "merge";
	case SM_UPDATE_REBASE:
		return "rebase";
	case SM_UPDATE_NONE:
		return "none";
	case SM_UPDATE_UNSPECIFIED:
		return NULL;
	case SM_UPDATE_COMMAND:
		strbuf_addf(&sb, "!%s", s->command);
		return strbuf_detach(&sb, NULL);
	}
	return NULL;
}