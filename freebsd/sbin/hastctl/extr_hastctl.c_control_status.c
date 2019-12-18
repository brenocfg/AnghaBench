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
struct nv {int dummy; } ;

/* Variables and functions */
 int nv_get_int16 (struct nv*,char*,unsigned int) ; 
 char* nv_get_string (struct nv*,char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
control_status(struct nv *nv)
{
	unsigned int ii;
	const char *str;
	int error, hprinted, ret;

	hprinted = 0;
	ret = 0;

	for (ii = 0; ; ii++) {
		str = nv_get_string(nv, "resource%u", ii);
		if (str == NULL)
			break;
		if (!hprinted) {
			printf("Name\tStatus\t Role\t\tComponents\n");
			hprinted = 1;
		}
		printf("%s\t", str);
		error = nv_get_int16(nv, "error%u", ii);
		if (error != 0) {
			if (ret == 0)
				ret = error;
			printf("ERR%d\n", error);
			continue;
		}
		str = nv_get_string(nv, "status%u", ii);
		printf("%-9s", (str != NULL) ? str : "-");
		printf("%-15s", nv_get_string(nv, "role%u", ii));
		printf("%s\t",
		    nv_get_string(nv, "localpath%u", ii));
		printf("%s\n",
		    nv_get_string(nv, "remoteaddr%u", ii));
	}
	return (ret);
}