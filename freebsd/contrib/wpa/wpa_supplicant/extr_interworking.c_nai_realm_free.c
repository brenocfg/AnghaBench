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
typedef  size_t u16 ;
struct nai_realm {struct nai_realm* realm; struct nai_realm* eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct nai_realm*) ; 

__attribute__((used)) static void nai_realm_free(struct nai_realm *realms, u16 count)
{
	u16 i;

	if (realms == NULL)
		return;
	for (i = 0; i < count; i++) {
		os_free(realms[i].eap);
		os_free(realms[i].realm);
	}
	os_free(realms);
}