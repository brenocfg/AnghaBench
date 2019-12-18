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
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int dummy; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_enabled ; 
 scalar_t__ biba_equal_effective (struct mac_biba*,struct mac_biba*) ; 

__attribute__((used)) static int
biba_bpfdesc_check_receive(struct bpf_d *d, struct label *dlabel,
    struct ifnet *ifp, struct label *ifplabel)
{
	struct mac_biba *a, *b;

	if (!biba_enabled)
		return (0);

	a = SLOT(dlabel);
	b = SLOT(ifplabel);

	if (biba_equal_effective(a, b))
		return (0);
	return (EACCES);
}