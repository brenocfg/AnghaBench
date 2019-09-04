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
struct upload_pack_data {int /*<<< orphan*/  deepen_not; int /*<<< orphan*/  shallows; int /*<<< orphan*/  haves; int /*<<< orphan*/  wanted_refs; int /*<<< orphan*/  wants; } ;

/* Variables and functions */
 int /*<<< orphan*/  object_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void upload_pack_data_clear(struct upload_pack_data *data)
{
	object_array_clear(&data->wants);
	string_list_clear(&data->wanted_refs, 1);
	oid_array_clear(&data->haves);
	object_array_clear(&data->shallows);
	string_list_clear(&data->deepen_not, 0);
}