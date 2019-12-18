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
typedef  scalar_t__ uint8_t ;
struct config_file {int num_tags; } ;
struct acl_list {int /*<<< orphan*/  region; } ;
struct acl_addr {size_t tag_actions_size; scalar_t__* tag_actions; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
 struct acl_addr* acl_find_or_create (struct acl_list*,char const*) ; 
 int find_tag_id (struct config_file*,char const*) ; 
 int /*<<< orphan*/  local_zone_str2type (char const*,int*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ regional_alloc_zero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acl_list_tag_action_cfg(struct acl_list* acl, struct config_file* cfg,
	const char* str, const char* tag, const char* action)
{
	struct acl_addr* node;
	int tagid;
	enum localzone_type t;
	if(!(node=acl_find_or_create(acl, str)))
		return 0;
	/* allocate array if not yet */
	if(!node->tag_actions) {
		node->tag_actions = (uint8_t*)regional_alloc_zero(acl->region,
			sizeof(*node->tag_actions)*cfg->num_tags);
		if(!node->tag_actions) {
			log_err("out of memory");
			return 0;
		}
		node->tag_actions_size = (size_t)cfg->num_tags;
	}
	/* parse tag */
	if((tagid=find_tag_id(cfg, tag)) == -1) {
		log_err("cannot parse tag (define-tag it): %s %s", str, tag);
		return 0;
	}
	if((size_t)tagid >= node->tag_actions_size) {
		log_err("tagid too large for array %s %s", str, tag);
		return 0;
	}
	if(!local_zone_str2type(action, &t)) {
		log_err("cannot parse access control action type: %s %s %s",
			str, tag, action);
		return 0;
	}
	node->tag_actions[tagid] = (uint8_t)t;
	return 1;
}