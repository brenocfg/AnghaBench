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
struct uuid {int dummy; } ;
struct g_part_uuid_alias {int mbrtype; scalar_t__ uuid; } ;

/* Variables and functions */
 scalar_t__ EQUUID (struct uuid*,scalar_t__) ; 
 struct g_part_uuid_alias* gpt_uuid_alias_match ; 

__attribute__((used)) static int
gpt_map_type(struct uuid *t)
{
	struct g_part_uuid_alias *uap;

	for (uap = &gpt_uuid_alias_match[0]; uap->uuid; uap++) {
		if (EQUUID(t, uap->uuid))
			return (uap->mbrtype);
	}
	return (0);
}