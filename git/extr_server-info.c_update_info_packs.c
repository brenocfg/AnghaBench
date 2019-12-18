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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_pack_info () ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int /*<<< orphan*/  init_pack_info (char*,int) ; 
 char* mkpathdup (char*,int /*<<< orphan*/ ) ; 
 int update_info_file (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_pack_info_file ; 

__attribute__((used)) static int update_info_packs(int force)
{
	char *infofile = mkpathdup("%s/info/packs", get_object_directory());
	int ret;

	init_pack_info(infofile, force);
	ret = update_info_file(infofile, write_pack_info_file, force);
	free_pack_info();
	free(infofile);
	return ret;
}