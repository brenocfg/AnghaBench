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
typedef  int /*<<< orphan*/  uint8_t ;
struct auth_zone {size_t namelen; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 struct auth_data* az_nsec3_find_exact (struct auth_zone*,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static struct auth_data*
az_nsec3_find_ce(struct auth_zone* z, uint8_t** cenm, size_t* cenmlen,
	int* no_exact_ce, int algo, size_t iter, uint8_t* salt, size_t saltlen)
{
	struct auth_data* node;
	while((node = az_nsec3_find_exact(z, *cenm, *cenmlen,
		algo, iter, salt, saltlen)) == NULL) {
		if(*cenmlen == z->namelen) {
			/* next step up would take us out of the zone. fail */
			return NULL;
		}
		*no_exact_ce = 1;
		dname_remove_label(cenm, cenmlen);
	}
	return node;
}