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

/* Variables and functions */
 int /*<<< orphan*/  fetch_fsck_objects ; 
 int /*<<< orphan*/  fetch_pack_config_cb ; 
 int /*<<< orphan*/  fetch_unpack_limit ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefer_ofs_delta ; 
 int /*<<< orphan*/  transfer_fsck_objects ; 
 int /*<<< orphan*/  transfer_unpack_limit ; 

__attribute__((used)) static void fetch_pack_config(void)
{
	git_config_get_int("fetch.unpacklimit", &fetch_unpack_limit);
	git_config_get_int("transfer.unpacklimit", &transfer_unpack_limit);
	git_config_get_bool("repack.usedeltabaseoffset", &prefer_ofs_delta);
	git_config_get_bool("fetch.fsckobjects", &fetch_fsck_objects);
	git_config_get_bool("transfer.fsckobjects", &transfer_fsck_objects);

	git_config(fetch_pack_config_cb, NULL);
}