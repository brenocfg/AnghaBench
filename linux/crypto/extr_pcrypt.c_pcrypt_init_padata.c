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
struct padata_instance {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct padata_instance* padata_alloc_possible (char const*) ; 
 int /*<<< orphan*/  padata_free (struct padata_instance*) ; 
 int pcrypt_sysfs_add (struct padata_instance*,char const*) ; 

__attribute__((used)) static int pcrypt_init_padata(struct padata_instance **pinst, const char *name)
{
	int ret = -ENOMEM;

	*pinst = padata_alloc_possible(name);
	if (!*pinst)
		return ret;

	ret = pcrypt_sysfs_add(*pinst, name);
	if (ret)
		padata_free(*pinst);

	return ret;
}