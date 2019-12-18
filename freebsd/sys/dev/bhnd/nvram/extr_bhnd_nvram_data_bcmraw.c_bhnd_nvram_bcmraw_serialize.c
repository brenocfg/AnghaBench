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
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;
typedef  int /*<<< orphan*/  bhnd_nvram_data_class ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_TYPE_STRING ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int EFTYPE ; 
 int ENOMEM ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/ * bhnd_nvram_plist_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_prop_encode (int /*<<< orphan*/ *,char*,size_t*,int /*<<< orphan*/ ) ; 
 char* bhnd_nvram_prop_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
bhnd_nvram_bcmraw_serialize(bhnd_nvram_data_class *cls, bhnd_nvram_plist *props,
    bhnd_nvram_plist *options, void *outp, size_t *olen)
{
	bhnd_nvram_prop	*prop;
	size_t		 limit, nbytes;
	int		 error;

	/* Determine output byte limit */
	if (outp != NULL)
		limit = *olen;
	else
		limit = 0;

	nbytes = 0;

	/* Write all properties */
	prop = NULL;
	while ((prop = bhnd_nvram_plist_next(props, prop)) != NULL) {
		const char	*name;
		char		*p;
		size_t		 prop_limit;
		size_t		 name_len, value_len;

		if (outp == NULL || limit < nbytes) {
			p = NULL;
			prop_limit = 0;
		} else {
			p = ((char *)outp) + nbytes;
			prop_limit = limit - nbytes;
		}

		/* Fetch and write name + '=' to output */
		name = bhnd_nvram_prop_name(prop);
		name_len = strlen(name) + 1;

		if (prop_limit > name_len) {
			memcpy(p, name, name_len - 1);
			p[name_len - 1] = '=';

			prop_limit -= name_len;
			p += name_len;
		} else {
			prop_limit = 0;
			p = NULL;
		}

		/* Advance byte count */
		if (SIZE_MAX - nbytes < name_len)
			return (EFTYPE); /* would overflow size_t */

		nbytes += name_len;

		/* Attempt to write NUL-terminated value to output */
		value_len = prop_limit;
		error = bhnd_nvram_prop_encode(prop, p, &value_len,
		    BHND_NVRAM_TYPE_STRING);

		/* If encoding failed for any reason other than ENOMEM (which
		 * we'll detect and report after encoding all properties),
		 * return immediately */
		if (error && error != ENOMEM) {
			BHND_NV_LOG("error serializing %s to required type "
			    "%s: %d\n", name,
			    bhnd_nvram_type_name(BHND_NVRAM_TYPE_STRING),
			    error);
			return (error);
		}

		/* Advance byte count */
		if (SIZE_MAX - nbytes < value_len)
			return (EFTYPE); /* would overflow size_t */

		nbytes += value_len;
	}

	/* Write terminating '\0' */
	if (limit > nbytes)
		*((char *)outp + nbytes) = '\0';

	if (nbytes == SIZE_MAX)
		return (EFTYPE); /* would overflow size_t */
	else
		nbytes++;

	/* Provide required length */
	*olen = nbytes;
	if (limit < *olen) {
		if (outp == NULL)
			return (0);

		return (ENOMEM);
	}

	return (0);
}