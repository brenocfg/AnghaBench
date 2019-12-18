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
struct respip_set {int dummy; } ;
struct resp_addr {scalar_t__ action; } ;
typedef  enum respip_action { ____Placeholder_respip_action } respip_action ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int respip_always_nxdomain ; 
 int respip_always_refuse ; 
 int respip_always_transparent ; 
 int respip_deny ; 
 struct resp_addr* respip_find_or_create (struct respip_set*,char const*,int) ; 
 int respip_inform ; 
 int respip_inform_deny ; 
 int respip_inform_redirect ; 
 scalar_t__ respip_none ; 
 int respip_redirect ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
respip_action_cfg(struct respip_set* set, const char* ipstr,
	const char* actnstr)
{
	struct resp_addr* node;
	enum respip_action action;

	if(!(node=respip_find_or_create(set, ipstr, 1)))
		return 0;
	if(node->action != respip_none) {
		verbose(VERB_QUERY, "duplicate response-ip action for '%s', overridden.",
			ipstr);
	}
        if(strcmp(actnstr, "deny") == 0)
                action = respip_deny;
        else if(strcmp(actnstr, "redirect") == 0)
                action = respip_redirect;
        else if(strcmp(actnstr, "inform") == 0)
                action = respip_inform;
        else if(strcmp(actnstr, "inform_deny") == 0)
                action = respip_inform_deny;
        else if(strcmp(actnstr, "inform_redirect") == 0)
                action = respip_inform_redirect;
        else if(strcmp(actnstr, "always_transparent") == 0)
                action = respip_always_transparent;
        else if(strcmp(actnstr, "always_refuse") == 0)
                action = respip_always_refuse;
        else if(strcmp(actnstr, "always_nxdomain") == 0)
                action = respip_always_nxdomain;
        else {
                log_err("unknown response-ip action %s", actnstr);
                return 0;
        }
	node->action = action;
	return 1;
}