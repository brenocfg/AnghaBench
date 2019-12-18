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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_STORAGE_AUTO ; 
 int bhnd_nvram_val_init_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_val_init(bhnd_nvram_val *value, const bhnd_nvram_val_fmt *fmt,
    const void *inp, size_t ilen, bhnd_nvram_type itype, uint32_t flags)
{
	int error;

	error = bhnd_nvram_val_init_common(value, BHND_NVRAM_VAL_STORAGE_AUTO,
	    fmt, inp, ilen, itype, flags);
	if (error)
		bhnd_nvram_val_release(value);

	return (error);
}