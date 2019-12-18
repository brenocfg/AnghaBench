#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bhnd_nvram_type ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ bhnd_nvram_prop ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 scalar_t__ bhnd_nvram_prop_type (TYPE_1__*) ; 
 void* bhnd_nvram_val_bytes (int /*<<< orphan*/ ,size_t*,scalar_t__*) ; 

const void *
bhnd_nvram_prop_bytes(bhnd_nvram_prop *prop, size_t *olen,
    bhnd_nvram_type *otype)
{
	const void *bytes;

	bytes = bhnd_nvram_val_bytes(prop->val, olen, otype);
	BHND_NV_ASSERT(*otype == bhnd_nvram_prop_type(prop), ("type mismatch"));

	return (bytes);
}