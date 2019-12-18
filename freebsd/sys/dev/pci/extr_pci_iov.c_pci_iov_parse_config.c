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
struct pcicfg_iov {int /*<<< orphan*/  iov_schema; } ;
struct pci_iov_arg {int /*<<< orphan*/  len; int /*<<< orphan*/  config; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  M_SRIOV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NV_FLAG_IGNORE_CASE ; 
 int copyin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int nvlist_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_unpack (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_max_config ; 
 int pci_iov_schema_validate_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pci_iov_parse_config(struct pcicfg_iov *iov, struct pci_iov_arg *arg,
    nvlist_t **ret)
{
	void *packed_config;
	nvlist_t *config;
	int error;

	config = NULL;
	packed_config = NULL;

	if (arg->len > pci_iov_max_config) {
		error = EMSGSIZE;
		goto out;
	}

	packed_config = malloc(arg->len, M_SRIOV, M_WAITOK);

	error = copyin(arg->config, packed_config, arg->len);
	if (error != 0)
		goto out;

	config = nvlist_unpack(packed_config, arg->len, NV_FLAG_IGNORE_CASE);
	if (config == NULL) {
		error = EINVAL;
		goto out;
	}

	error = pci_iov_schema_validate_config(iov->iov_schema, config);
	if (error != 0)
		goto out;

	error = nvlist_error(config);
	if (error != 0)
		goto out;

	*ret = config;
	config = NULL;

out:
	nvlist_destroy(config);
	free(packed_config, M_SRIOV);
	return (error);
}