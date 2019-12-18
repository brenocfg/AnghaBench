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
struct libbe_deep_clone {char* bename; TYPE_1__* lbh; } ;
struct TYPE_2__ {char* root; } ;

/* Variables and functions */
 int BE_ERR_BADPATH ; 
 int BE_ERR_SUCCESS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
be_get_path(struct libbe_deep_clone *ldc, const char *dspath, char *result, int result_size)
{
	char *pos;
	char *child_dataset;

	/* match the root path for the boot environments */
	pos = strstr(dspath, ldc->lbh->root);

	/* no match, different pools? */
	if (pos == NULL)
		return (BE_ERR_BADPATH);

	/* root path of the new boot environment */
	snprintf(result, result_size, "%s/%s", ldc->lbh->root, ldc->bename);

        /* gets us to the parent dataset, the +1 consumes a trailing slash */
	pos += strlen(ldc->lbh->root) + 1;

	/* skip the parent dataset */
	if ((child_dataset = strchr(pos, '/')) != NULL)
		strlcat(result, child_dataset, result_size);

	return (BE_ERR_SUCCESS);
}