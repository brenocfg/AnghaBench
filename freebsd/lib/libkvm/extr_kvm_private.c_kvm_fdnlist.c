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
struct nlist {char* n_name; int n_type; int /*<<< orphan*/  n_value; } ;
struct kvm_nlist {char* n_name; int n_type; int /*<<< orphan*/  n_value; } ;
struct TYPE_3__ {int (* resolve_symbol ) (char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  nlfd; } ;
typedef  TYPE_1__ kvm_t ;
typedef  int /*<<< orphan*/  kvaddr_t ;

/* Variables and functions */
 int N_DATA ; 
 int N_EXT ; 
 int __fdnlist (int /*<<< orphan*/ ,struct nlist*) ; 
 struct nlist* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct nlist*) ; 
 int stub1 (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kvm_fdnlist(kvm_t *kd, struct kvm_nlist *list)
{
	kvaddr_t addr;
	int error, nfail;

	if (kd->resolve_symbol == NULL) {
		struct nlist *nl;
		int count, i;

		for (count = 0; list[count].n_name != NULL &&
		     list[count].n_name[0] != '\0'; count++)
			;
		nl = calloc(count + 1, sizeof(*nl));
		for (i = 0; i < count; i++)
			nl[i].n_name = list[i].n_name;
		nfail = __fdnlist(kd->nlfd, nl);
		for (i = 0; i < count; i++) {
			list[i].n_type = nl[i].n_type;
			list[i].n_value = nl[i].n_value;
		}
		free(nl);
		return (nfail);
	}

	nfail = 0;
	while (list->n_name != NULL && list->n_name[0] != '\0') {
		error = kd->resolve_symbol(list->n_name, &addr);
		if (error != 0) {
			nfail++;
			list->n_value = 0;
			list->n_type = 0;
		} else {
			list->n_value = addr;
			list->n_type = N_DATA | N_EXT;
		}
		list++;
	}
	return (nfail);
}