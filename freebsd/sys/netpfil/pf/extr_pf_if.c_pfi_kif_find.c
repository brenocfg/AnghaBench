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
struct pfi_kif_cmp {int /*<<< orphan*/  pfik_name; } ;
struct pfi_kif {int dummy; } ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  PF_RULES_ASSERT () ; 
 struct pfi_kif* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  V_pfi_ifs ; 
 int /*<<< orphan*/  bzero (struct pfi_kif_cmp*,int) ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct pfi_kif *
pfi_kif_find(const char *kif_name)
{
	struct pfi_kif_cmp s;

	PF_RULES_ASSERT();

	bzero(&s, sizeof(s));
	strlcpy(s.pfik_name, kif_name, sizeof(s.pfik_name));

	return (RB_FIND(pfi_ifhead, &V_pfi_ifs, (struct pfi_kif *)&s));
}