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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int kldload (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int
ngtype_load(const u_char *name, size_t namelen)
{
	char *mod;
	int ret;

	if ((mod = malloc(namelen + 4)) == NULL)
		return (-1);
	strcpy(mod, "ng_");
	strncpy(mod + 3, name, namelen);
	mod[namelen + 3] = '\0';

	ret = kldload(mod);
	free(mod);
	return (ret);
}