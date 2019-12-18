#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const_efidp ;
struct TYPE_2__ {int /*<<< orphan*/  PathName; } ;
typedef  TYPE_1__ FILEPATH_DEVICE_PATH ;

/* Variables and functions */
 int /*<<< orphan*/  ucs2_to_utf8 (int /*<<< orphan*/ ,char**) ; 

char *
efidp_extract_file_path(const_efidp dp)
{
	const FILEPATH_DEVICE_PATH  *fp;
	char *name = NULL;

	fp = (const void *)dp;
	ucs2_to_utf8(fp->PathName, &name);
	return name;
}