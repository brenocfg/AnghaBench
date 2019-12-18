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
struct bhnd_nvram_tlv_env {char* envp; } ;
struct bhnd_nvram_tlv {scalar_t__ count; int /*<<< orphan*/ * data; } ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t NVRAM_TLV_ENVP_DATA_LEN (struct bhnd_nvram_tlv_env*) ; 
 int /*<<< orphan*/ * bhnd_nvram_iobuf_copy_range (struct bhnd_nvram_io*,int,size_t) ; 
 int bhnd_nvram_parse_env (char*,size_t,char,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bhnd_nvram_tlv_env* bhnd_nvram_tlv_next_env (struct bhnd_nvram_tlv*,size_t*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_tlv_parse_size (struct bhnd_nvram_io*,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_tlv_init(struct bhnd_nvram_tlv *tlv, struct bhnd_nvram_io *src)
{
	struct bhnd_nvram_tlv_env	*env;
	size_t				 size;
	size_t				 next;
	int				 error;

	BHND_NV_ASSERT(tlv->data == NULL, ("tlv data already initialized"));

	/* Determine the actual size of the TLV source data */
	if ((error = bhnd_nvram_tlv_parse_size(src, &size)))
		return (error);

	/* Copy to our own internal buffer */
	if ((tlv->data = bhnd_nvram_iobuf_copy_range(src, 0x0, size)) == NULL)
		return (ENOMEM);

	/* Initialize our backing buffer */
	tlv->count = 0;
	next = 0;
	while ((env = bhnd_nvram_tlv_next_env(tlv, &next, NULL)) != NULL) {
		size_t env_len;
		size_t name_len;

		/* TLV_ENV data must not be empty */
		env_len = NVRAM_TLV_ENVP_DATA_LEN(env);
		if (env_len == 0) {
			BHND_NV_LOG("cannot parse zero-length TLV_ENV record "
			    "data\n");
			return (EINVAL);
		}

		/* Parse the key=value string, and then replace the '='
		 * delimiter with '\0' to allow us to provide direct 
		 * name pointers from our backing buffer */
		error = bhnd_nvram_parse_env(env->envp, env_len, '=', NULL,
		    &name_len, NULL, NULL);
		if (error) {
			BHND_NV_LOG("error parsing TLV_ENV data: %d\n", error);
			return (error);
		}

		/* Replace '=' with '\0' */
		*(env->envp + name_len) = '\0';

		/* Add to variable count */
		tlv->count++;
	};

	return (0);
}