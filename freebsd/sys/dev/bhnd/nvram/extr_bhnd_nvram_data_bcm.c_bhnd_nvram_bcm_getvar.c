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
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int bhnd_nvram_data_generic_rp_getvar (struct bhnd_nvram_data*,void*,void*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_nvram_bcm_getvar(struct bhnd_nvram_data *nv, void *cookiep, void *buf,
    size_t *len, bhnd_nvram_type type)
{
	return (bhnd_nvram_data_generic_rp_getvar(nv, cookiep, buf, len, type));
}