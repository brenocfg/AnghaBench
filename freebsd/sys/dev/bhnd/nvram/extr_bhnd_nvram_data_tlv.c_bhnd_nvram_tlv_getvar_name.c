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
struct bhnd_nvram_tlv_env {char const* envp; } ;
struct bhnd_nvram_tlv {int dummy; } ;
struct bhnd_nvram_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_PANIC (char*,void*) ; 
 struct bhnd_nvram_tlv_env* bhnd_nvram_tlv_get_env (struct bhnd_nvram_tlv*,void*) ; 

__attribute__((used)) static const char *
bhnd_nvram_tlv_getvar_name(struct bhnd_nvram_data *nv, void *cookiep)
{
	struct bhnd_nvram_tlv		*tlv;
	const struct bhnd_nvram_tlv_env	*env;

	tlv = (struct bhnd_nvram_tlv *)nv;

	/* Fetch pointer to the TLV_ENV record */
	if ((env = bhnd_nvram_tlv_get_env(tlv, cookiep)) == NULL)
		BHND_NV_PANIC("invalid cookiep: %p", cookiep);

	/* Return name pointer */
	return (&env->envp[0]);
}