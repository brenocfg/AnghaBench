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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  i386_pte_pae_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _kvm_pmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static i386_pte_pae_t
_i386_pte_pae_get(kvm_t *kd, u_long pteindex)
{
	i386_pte_pae_t *pte = _kvm_pmap_get(kd, pteindex, sizeof(*pte));

	return le64toh(*pte);
}