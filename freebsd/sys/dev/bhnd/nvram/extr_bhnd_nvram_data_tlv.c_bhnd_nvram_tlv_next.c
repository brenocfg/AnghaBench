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
 int /*<<< orphan*/  BHND_NV_PANIC (char*) ; 
 struct bhnd_nvram_tlv_env* bhnd_nvram_tlv_next_env (struct bhnd_nvram_tlv*,size_t*,void**) ; 
 size_t bhnd_nvram_tlv_to_offset (struct bhnd_nvram_tlv*,void*) ; 

__attribute__((used)) static const char *
bhnd_nvram_tlv_next(struct bhnd_nvram_data *nv, void **cookiep)
{
	struct bhnd_nvram_tlv		*tlv;
	struct bhnd_nvram_tlv_env	*env;
	size_t				 io_offset;

	tlv = (struct bhnd_nvram_tlv *)nv;

	/* Find next readable TLV record */
	if (*cookiep == NULL) {
		/* Start search at offset 0x0 */
		io_offset = 0x0;
		env = bhnd_nvram_tlv_next_env(tlv, &io_offset, cookiep);
	} else {
		/* Seek past the previous env record */
		io_offset = bhnd_nvram_tlv_to_offset(tlv, *cookiep);
		env = bhnd_nvram_tlv_next_env(tlv, &io_offset, NULL);
		if (env == NULL)
			BHND_NV_PANIC("invalid cookiep; record missing");

		/* Advance to next env record, update the caller's cookiep */
		env = bhnd_nvram_tlv_next_env(tlv, &io_offset, cookiep);
	}

	/* Check for EOF */
	if (env == NULL)
		return (NULL);

	/* Return the NUL terminated name */
	return (env->envp);
}