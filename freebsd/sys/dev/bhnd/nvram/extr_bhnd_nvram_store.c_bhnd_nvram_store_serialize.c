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
struct bhnd_nvram_store {int dummy; } ;
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;
typedef  int /*<<< orphan*/  bhnd_nvram_data_class ;

/* Variables and functions */
 int ENOMEM ; 
 int bhnd_nvram_data_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t*) ; 
 int /*<<< orphan*/  bhnd_nvram_io_free (struct bhnd_nvram_io*) ; 
 int bhnd_nvram_io_setsize (struct bhnd_nvram_io*,size_t) ; 
 int bhnd_nvram_io_write_ptr (struct bhnd_nvram_io*,int /*<<< orphan*/ ,void**,size_t,int /*<<< orphan*/ *) ; 
 struct bhnd_nvram_io* bhnd_nvram_iobuf_empty (size_t,size_t) ; 
 int /*<<< orphan*/  bhnd_nvram_plist_release (int /*<<< orphan*/ *) ; 
 int bhnd_nvram_store_export (struct bhnd_nvram_store*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_store_serialize(struct bhnd_nvram_store *sc, const char *path,
   struct bhnd_nvram_io **data,  uint32_t flags)
{
	bhnd_nvram_plist	*props;
	bhnd_nvram_plist	*options;
	bhnd_nvram_data_class	*cls;
	struct bhnd_nvram_io	*io;
	void			*outp;
	size_t			 olen;
	int			 error;

	props = NULL;
	options = NULL;
	io = NULL;

	/* Perform requested export */
	error = bhnd_nvram_store_export(sc, path, &cls, &props, &options,
	    flags);
	if (error)
		return (error);

	/* Determine serialized size */
	error = bhnd_nvram_data_serialize(cls, props, options, NULL, &olen);
	if (error)
		goto failed;

	/* Allocate output buffer */
	if ((io = bhnd_nvram_iobuf_empty(olen, olen)) == NULL) {
		error = ENOMEM;
		goto failed;
	}

	/* Fetch write pointer */
	if ((error = bhnd_nvram_io_write_ptr(io, 0, &outp, olen, NULL)))
		goto failed;

	/* Perform serialization */
	error = bhnd_nvram_data_serialize(cls, props, options, outp, &olen);
	if (error)
		goto failed;

	if ((error = bhnd_nvram_io_setsize(io, olen)))
		goto failed;

	/* Success */
	bhnd_nvram_plist_release(props);
	bhnd_nvram_plist_release(options);

	*data = io;
	return (0);

failed:
	if (props != NULL)
		bhnd_nvram_plist_release(props);

	if (options != NULL)
		bhnd_nvram_plist_release(options);

	if (io != NULL)
		bhnd_nvram_io_free(io);

	return (error);
}