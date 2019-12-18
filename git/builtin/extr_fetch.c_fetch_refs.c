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
struct transport {int dummy; } ;
struct ref {int dummy; } ;

/* Variables and functions */
 int check_exist_and_connected (struct ref*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,int /*<<< orphan*/ ) ; 
 int transport_fetch_refs (struct transport*,struct ref*) ; 
 int /*<<< orphan*/  transport_unlock_pack (struct transport*) ; 

__attribute__((used)) static int fetch_refs(struct transport *transport, struct ref *ref_map)
{
	int ret = check_exist_and_connected(ref_map);
	if (ret) {
		trace2_region_enter("fetch", "fetch_refs", the_repository);
		ret = transport_fetch_refs(transport, ref_map);
		trace2_region_leave("fetch", "fetch_refs", the_repository);
	}
	if (!ret)
		/*
		 * Keep the new pack's ".keep" file around to allow the caller
		 * time to update refs to reference the new objects.
		 */
		return 0;
	transport_unlock_pack(transport);
	return ret;
}