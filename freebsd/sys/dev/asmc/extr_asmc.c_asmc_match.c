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
struct asmc_model {scalar_t__ smc_model; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct asmc_model* asmc_models ; 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct asmc_model *
asmc_match(device_t dev)
{
	int i;
	char *model;

	model = kern_getenv("smbios.system.product");
	if (model == NULL)
		return (NULL);

	for (i = 0; asmc_models[i].smc_model; i++) {
		if (!strncmp(model, asmc_models[i].smc_model, strlen(model))) {
			freeenv(model);
			return (&asmc_models[i]);
		}
	}
	freeenv(model);

	return (NULL);
}