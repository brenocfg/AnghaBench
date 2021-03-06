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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_val_fmt ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_STORAGE_AUTO ; 
 int bhnd_nvram_val_convert_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_val_convert_init(bhnd_nvram_val *value,
    const bhnd_nvram_val_fmt *fmt, bhnd_nvram_val *src, uint32_t flags)
{
	int error;

	error = bhnd_nvram_val_convert_common(value,
	    BHND_NVRAM_VAL_STORAGE_AUTO, fmt, src, flags);
	if (error)
		bhnd_nvram_val_release(value);

	return (error);
}