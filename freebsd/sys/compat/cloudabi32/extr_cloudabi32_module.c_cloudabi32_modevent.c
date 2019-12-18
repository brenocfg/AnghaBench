#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_5__ {int /*<<< orphan*/  sysvec; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  _binary_cloudabi32_vdso_o_end ; 
 int /*<<< orphan*/  _binary_cloudabi32_vdso_o_start ; 
 TYPE_1__ cloudabi32_brand ; 
 int /*<<< orphan*/  cloudabi_vdso_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cloudabi_vdso_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf32_brand_inuse (TYPE_1__*) ; 
 int /*<<< orphan*/  elf32_insert_brand_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  elf32_remove_brand_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
cloudabi32_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		cloudabi_vdso_init(cloudabi32_brand.sysvec,
		    _binary_cloudabi32_vdso_o_start,
		    _binary_cloudabi32_vdso_o_end);
		if (elf32_insert_brand_entry(&cloudabi32_brand) < 0) {
			printf("Failed to add CloudABI ELF brand handler\n");
			return (EINVAL);
		}
		return (0);
	case MOD_UNLOAD:
		if (elf32_brand_inuse(&cloudabi32_brand))
			return (EBUSY);
		if (elf32_remove_brand_entry(&cloudabi32_brand) < 0) {
			printf("Failed to remove CloudABI ELF brand handler\n");
			return (EINVAL);
		}
		cloudabi_vdso_destroy(cloudabi32_brand.sysvec);
		return (0);
	default:
		return (EOPNOTSUPP);
	}
}