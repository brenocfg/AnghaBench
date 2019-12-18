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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
#define  ID_AA64ISAR0_AES_BASE 129 
#define  ID_AA64ISAR0_AES_PMULL 128 
 int ID_AA64ISAR0_AES_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  id_aa64isar0_el1 ; 

__attribute__((used)) static int
armv8_crypto_probe(device_t dev)
{
	uint64_t reg;
	int ret = ENXIO;

	reg = READ_SPECIALREG(id_aa64isar0_el1);

	switch (ID_AA64ISAR0_AES_VAL(reg)) {
	case ID_AA64ISAR0_AES_BASE:
	case ID_AA64ISAR0_AES_PMULL:
		ret = 0;
		break;
	}

	device_set_desc_copy(dev, "AES-CBC");

	/* TODO: Check more fields as we support more features */

	return (ret);
}