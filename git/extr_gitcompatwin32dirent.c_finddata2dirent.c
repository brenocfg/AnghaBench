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
struct dirent {int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_name; } ;
struct TYPE_3__ {int dwFileAttributes; int /*<<< orphan*/  cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAW ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_REG ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  xwcstoutf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void finddata2dirent(struct dirent *ent, WIN32_FIND_DATAW *fdata)
{
	/* convert UTF-16 name to UTF-8 */
	xwcstoutf(ent->d_name, fdata->cFileName, sizeof(ent->d_name));

	/* Set file type, based on WIN32_FIND_DATA */
	if (fdata->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		ent->d_type = DT_DIR;
	else
		ent->d_type = DT_REG;
}