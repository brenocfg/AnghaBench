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
struct bhnd_nvram_io {int dummy; } ;
struct bhnd_nvram_bcmraw {size_t size; int /*<<< orphan*/ * data; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,size_t,...) ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/ * bhnd_nv_malloc (size_t) ; 
 int /*<<< orphan*/ * bhnd_nv_reallocf (int /*<<< orphan*/ *,size_t) ; 
 size_t bhnd_nvram_io_getsize (struct bhnd_nvram_io*) ; 
 int bhnd_nvram_io_read (struct bhnd_nvram_io*,int,int /*<<< orphan*/ *,size_t) ; 
 int bhnd_nvram_parse_env (char*,size_t,char,char const**,size_t*,char const**,size_t*) ; 
 size_t strnlen (char*,size_t) ; 

__attribute__((used)) static int
bhnd_nvram_bcmraw_init(struct bhnd_nvram_bcmraw *bcm, struct bhnd_nvram_io *src)
{
	size_t	 io_size;
	size_t	 capacity, offset;
	int	 error;

	/* Fetch the input image size */
	io_size = bhnd_nvram_io_getsize(src);

	/* Allocate a buffer large enough to hold the NVRAM image, and
	 * an extra EOF-signaling NUL (on the chance it's missing from the
	 * source data) */
	if (io_size == SIZE_MAX)
		return (ENOMEM);

	capacity = io_size + 1 /* room for extra NUL */;
	bcm->size = io_size;
	if ((bcm->data = bhnd_nv_malloc(capacity)) == NULL)
		return (ENOMEM);

	/* Copy in the NVRAM image */
	if ((error = bhnd_nvram_io_read(src, 0x0, bcm->data, io_size)))
		return (error);

	/* Process the buffer */
	bcm->count = 0;
	for (offset = 0; offset < bcm->size; offset++) {
		char		*envp;
		const char	*name, *value;
		size_t		 envp_len;
		size_t		 name_len, value_len;

		/* Parse the key=value string */
		envp = (char *) (bcm->data + offset);
		envp_len = strnlen(envp, bcm->size - offset);
		error = bhnd_nvram_parse_env(envp, envp_len, '=', &name,
					     &name_len, &value, &value_len);
		if (error) {
			BHND_NV_LOG("error parsing envp at offset %#zx: %d\n",
			    offset, error);
			return (error);
		}

		/* Insert a '\0' character, replacing the '=' delimiter and
		 * allowing us to vend references directly to the variable
		 * name */
		*(envp + name_len) = '\0';

		/* Add to variable count */
		bcm->count++;

		/* Seek past the value's terminating '\0' */
		offset += envp_len;
		if (offset == io_size) {
			BHND_NV_LOG("missing terminating NUL at offset %#zx\n",
			    offset);
			return (EINVAL);
		}

		/* If we hit EOF without finding a terminating NUL
		 * byte, we need to append it */
		if (++offset == bcm->size) {
			BHND_NV_ASSERT(offset < capacity,
			    ("appending past end of buffer"));
			bcm->size++;
			*(bcm->data + offset) = '\0';
		}

		/* Check for explicit EOF (encoded as a single empty NUL
		 * terminated string) */
		if (*(bcm->data + offset) == '\0')
			break;
	}

	/* Reclaim any unused space in he backing buffer */
	if (offset < bcm->size) {
		bcm->data = bhnd_nv_reallocf(bcm->data, bcm->size);
		if (bcm->data == NULL)
			return (ENOMEM);
	}

	return (0);
}