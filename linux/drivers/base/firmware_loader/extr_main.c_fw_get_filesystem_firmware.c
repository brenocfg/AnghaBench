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
struct fw_priv {size_t allocated_size; char* fw_name; size_t size; void* data; } ;
struct device {int dummy; } ;
typedef  size_t loff_t ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 size_t INT_MAX ; 
 int PATH_MAX ; 
 int READING_FIRMWARE ; 
 int READING_FIRMWARE_PREALLOC_BUFFER ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*,int) ; 
 int /*<<< orphan*/  fw_free_paged_buf (struct fw_priv*) ; 
 char** fw_path ; 
 int /*<<< orphan*/  fw_state_done (struct fw_priv*) ; 
 int kernel_read_file_from_path (char*,void**,size_t*,size_t,int) ; 
 int snprintf (char*,int,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static int
fw_get_filesystem_firmware(struct device *device, struct fw_priv *fw_priv,
			   const char *suffix,
			   int (*decompress)(struct device *dev,
					     struct fw_priv *fw_priv,
					     size_t in_size,
					     const void *in_buffer))
{
	loff_t size;
	int i, len;
	int rc = -ENOENT;
	char *path;
	enum kernel_read_file_id id = READING_FIRMWARE;
	size_t msize = INT_MAX;
	void *buffer = NULL;

	/* Already populated data member means we're loading into a buffer */
	if (!decompress && fw_priv->data) {
		buffer = fw_priv->data;
		id = READING_FIRMWARE_PREALLOC_BUFFER;
		msize = fw_priv->allocated_size;
	}

	path = __getname();
	if (!path)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(fw_path); i++) {
		/* skip the unset customized path */
		if (!fw_path[i][0])
			continue;

		len = snprintf(path, PATH_MAX, "%s/%s%s",
			       fw_path[i], fw_priv->fw_name, suffix);
		if (len >= PATH_MAX) {
			rc = -ENAMETOOLONG;
			break;
		}

		fw_priv->size = 0;
		rc = kernel_read_file_from_path(path, &buffer, &size,
						msize, id);
		if (rc) {
			if (rc != -ENOENT)
				dev_warn(device, "loading %s failed with error %d\n",
					 path, rc);
			else
				dev_dbg(device, "loading %s failed for no such file or directory.\n",
					 path);
			continue;
		}
		if (decompress) {
			dev_dbg(device, "f/w decompressing %s\n",
				fw_priv->fw_name);
			rc = decompress(device, fw_priv, size, buffer);
			/* discard the superfluous original content */
			vfree(buffer);
			buffer = NULL;
			if (rc) {
				fw_free_paged_buf(fw_priv);
				continue;
			}
		} else {
			dev_dbg(device, "direct-loading %s\n",
				fw_priv->fw_name);
			if (!fw_priv->data)
				fw_priv->data = buffer;
			fw_priv->size = size;
		}
		fw_state_done(fw_priv);
		break;
	}
	__putname(path);

	return rc;
}