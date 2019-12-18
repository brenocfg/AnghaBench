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
struct preloaded_file {int /*<<< orphan*/  f_addr; } ;
struct fdt_header {int dummy; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  COPYOUT (int /*<<< orphan*/ ,struct fdt_header*,int) ; 
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  debugf (char*,char const*) ; 
 int fdt_check_header (struct fdt_header*) ; 
 int /*<<< orphan*/  file_discard (struct preloaded_file*) ; 
 struct preloaded_file* file_loadraw (char const*,char*,int) ; 

__attribute__((used)) static int
fdt_load_dtb_overlay(const char * filename)
{
	struct preloaded_file *bfp;
	struct fdt_header header;
	int err;

	debugf("fdt_load_dtb_overlay(%s)\n", filename);

	/* Attempt to load and validate a new dtb from a file. FDT_ERR_NOTFOUND
	 * is normally a libfdt error code, but libfdt would actually return
	 * -FDT_ERR_NOTFOUND. We re-purpose the error code here to convey a
	 * similar meaning: the file itself was not found, which can still be
	 * considered an error dealing with FDT pieces.
	 */
	if ((bfp = file_loadraw(filename, "dtbo", 1)) == NULL)
		return (FDT_ERR_NOTFOUND);

	COPYOUT(bfp->f_addr, &header, sizeof(header));
	err = fdt_check_header(&header);

	if (err < 0) {
		file_discard(bfp);
		return (err);
	}

	return (0);
}