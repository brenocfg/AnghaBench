#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__* e_ident; } ;
struct TYPE_5__ {TYPE_1__ nlehdr; } ;
typedef  TYPE_2__ kvm_t ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2LSB ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint64_t
_kvm64toh(kvm_t *kd, uint64_t val)
{

	if (kd->nlehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		return (le64toh(val));
	else
		return (be64toh(val));
}