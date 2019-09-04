#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct oid_array {int nr; } ;
struct object_id {int dummy; } ;
struct git_transport_options {struct oid_array* negotiation_tips; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_oid ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  for_each_glob_ref (int /*<<< orphan*/ ,char const*,struct oid_array*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  has_glob_specials (char const*) ; 
 TYPE_2__ negotiation_tip ; 
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 
 struct oid_array* xcalloc (int,int) ; 

__attribute__((used)) static void add_negotiation_tips(struct git_transport_options *smart_options)
{
	struct oid_array *oids = xcalloc(1, sizeof(*oids));
	int i;

	for (i = 0; i < negotiation_tip.nr; i++) {
		const char *s = negotiation_tip.items[i].string;
		int old_nr;
		if (!has_glob_specials(s)) {
			struct object_id oid;
			if (get_oid(s, &oid))
				die("%s is not a valid object", s);
			oid_array_append(oids, &oid);
			continue;
		}
		old_nr = oids->nr;
		for_each_glob_ref(add_oid, s, oids);
		if (old_nr == oids->nr)
			warning("Ignoring --negotiation-tip=%s because it does not match any refs",
				s);
	}
	smart_options->negotiation_tips = oids;
}