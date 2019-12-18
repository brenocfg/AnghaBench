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
typedef  scalar_t__ uint8_t ;
struct bhnd_nvram_tlv_env {int dummy; } ;
struct bhnd_nvram_tlv {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 scalar_t__ NVRAM_TLV_TYPE_END ; 
 scalar_t__ NVRAM_TLV_TYPE_ENV ; 
 struct bhnd_nvram_tlv_env* bhnd_nvram_tlv_get_env (struct bhnd_nvram_tlv*,void*) ; 
 int bhnd_nvram_tlv_next_record (int /*<<< orphan*/ ,size_t*,size_t*,scalar_t__*) ; 
 void* bhnd_nvram_tlv_to_cookie (struct bhnd_nvram_tlv*,size_t) ; 

__attribute__((used)) static struct bhnd_nvram_tlv_env *
bhnd_nvram_tlv_next_env(struct bhnd_nvram_tlv *tlv, size_t *next,
    void **cookiep)
{
	uint8_t	tag;
	int	error;

	/* Find the next TLV_ENV record, starting at @p next */
	do {
		void	*c;
		size_t	 offset;

		/* Fetch the next TLV record */
		error = bhnd_nvram_tlv_next_record(tlv->data, next, &offset,
		    &tag);
		if (error) {
			BHND_NV_LOG("unexpected error in next_record(): %d\n",
			    error);
			return (NULL);
		}

		/* Only interested in ENV records */
		if (tag != NVRAM_TLV_TYPE_ENV)
			continue;

		/* Map and return TLV_ENV record pointer */
		c = bhnd_nvram_tlv_to_cookie(tlv, offset);

		/* Provide the cookiep value for the returned record */
		if (cookiep != NULL)
			*cookiep = c;

		return (bhnd_nvram_tlv_get_env(tlv, c));
	} while (tag != NVRAM_TLV_TYPE_END);

	/* No remaining ENV records */
	return (NULL);
}