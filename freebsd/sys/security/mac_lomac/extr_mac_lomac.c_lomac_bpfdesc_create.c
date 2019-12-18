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
struct ucred {struct label* cr_label; } ;
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  lomac_copy_single (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static void
lomac_bpfdesc_create(struct ucred *cred, struct bpf_d *d,
    struct label *dlabel)
{
	struct mac_lomac *source, *dest;

	source = SLOT(cred->cr_label);
	dest = SLOT(dlabel);

	lomac_copy_single(source, dest);
}