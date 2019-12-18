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
typedef  int /*<<< orphan*/  timestamp_t ;
struct rev_info {int dummy; } ;
struct recent_data {int /*<<< orphan*/  timestamp; struct rev_info* revs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOR_EACH_OBJECT_LOCAL_ONLY ; 
 int /*<<< orphan*/  add_recent_loose ; 
 int /*<<< orphan*/  add_recent_packed ; 
 int for_each_loose_object (int /*<<< orphan*/ ,struct recent_data*,int /*<<< orphan*/ ) ; 
 int for_each_packed_object (int /*<<< orphan*/ ,struct recent_data*,int /*<<< orphan*/ ) ; 

int add_unseen_recent_objects_to_traversal(struct rev_info *revs,
					   timestamp_t timestamp)
{
	struct recent_data data;
	int r;

	data.revs = revs;
	data.timestamp = timestamp;

	r = for_each_loose_object(add_recent_loose, &data,
				  FOR_EACH_OBJECT_LOCAL_ONLY);
	if (r)
		return r;
	return for_each_packed_object(add_recent_packed, &data,
				      FOR_EACH_OBJECT_LOCAL_ONLY);
}