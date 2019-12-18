#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msdos_options {int volume_id_set; int media_descriptor_set; int hidden_sectors_set; int timestamp_set; int /*<<< orphan*/  timestamp; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ option_t ;
struct TYPE_7__ {TYPE_1__* fs_options; struct msdos_options* fs_specific; } ;
typedef  TYPE_2__ fsinfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  st_mtime; scalar_t__ st_ino; } ;

/* Variables and functions */
 int DEBUG_FS_PARSE_OPTS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int set_option (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ stampst ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int
msdos_parse_opts(const char *option, fsinfo_t *fsopts)
{
	struct msdos_options *msdos_opt = fsopts->fs_specific;
	option_t *msdos_options = fsopts->fs_options;
	int rv;

	assert(option != NULL);
	assert(fsopts != NULL);
	assert(msdos_opt != NULL);

	if (debug & DEBUG_FS_PARSE_OPTS)
		printf("msdos_parse_opts: got `%s'\n", option);

	rv = set_option(msdos_options, option, NULL, 0);
	if (rv == -1)
		return rv;

	if (strcmp(msdos_options[rv].name, "volume_id") == 0)
		msdos_opt->volume_id_set = 1;
	else if (strcmp(msdos_options[rv].name, "media_descriptor") == 0)
		msdos_opt->media_descriptor_set = 1;
	else if (strcmp(msdos_options[rv].name, "hidden_sectors") == 0)
		msdos_opt->hidden_sectors_set = 1;

	if (stampst.st_ino) {
		msdos_opt->timestamp_set = 1;
		msdos_opt->timestamp = stampst.st_mtime;
	}

	return 1;
}