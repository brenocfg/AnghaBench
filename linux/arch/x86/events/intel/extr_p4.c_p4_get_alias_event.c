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
typedef  int u64 ;
struct TYPE_3__ {int original; int alternative; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int P4_CONFIG_ALIASABLE ; 
 int P4_CONFIG_EVENT_ALIAS_IMMUTABLE_BITS ; 
 int P4_CONFIG_EVENT_ALIAS_MASK ; 
 TYPE_1__* p4_event_aliases ; 

__attribute__((used)) static u64 p4_get_alias_event(u64 config)
{
	u64 config_match;
	int i;

	/*
	 * Only event with special mark is allowed,
	 * we're to be sure it didn't come as malformed
	 * RAW event.
	 */
	if (!(config & P4_CONFIG_ALIASABLE))
		return 0;

	config_match = config & P4_CONFIG_EVENT_ALIAS_MASK;

	for (i = 0; i < ARRAY_SIZE(p4_event_aliases); i++) {
		if (config_match == p4_event_aliases[i].original) {
			config_match = p4_event_aliases[i].alternative;
			break;
		} else if (config_match == p4_event_aliases[i].alternative) {
			config_match = p4_event_aliases[i].original;
			break;
		}
	}

	if (i >= ARRAY_SIZE(p4_event_aliases))
		return 0;

	return config_match | (config & P4_CONFIG_EVENT_ALIAS_IMMUTABLE_BITS);
}