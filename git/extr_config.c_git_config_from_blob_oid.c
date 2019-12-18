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
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ORIGIN_BLOB ; 
 int OBJ_BLOB ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int git_config_from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,unsigned long,void*,int /*<<< orphan*/ *) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 

int git_config_from_blob_oid(config_fn_t fn,
			      const char *name,
			      const struct object_id *oid,
			      void *data)
{
	enum object_type type;
	char *buf;
	unsigned long size;
	int ret;

	buf = read_object_file(oid, &type, &size);
	if (!buf)
		return error(_("unable to load config blob object '%s'"), name);
	if (type != OBJ_BLOB) {
		free(buf);
		return error(_("reference '%s' does not point to a blob"), name);
	}

	ret = git_config_from_mem(fn, CONFIG_ORIGIN_BLOB, name, buf, size,
				  data, NULL);
	free(buf);

	return ret;
}