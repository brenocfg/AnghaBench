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
struct userdiff_driver {int dummy; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_filespec {int dummy; } ;

/* Variables and functions */
 struct diff_filespec* alloc_filespec (char const*) ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,struct object_id const*,int,unsigned int) ; 
 unsigned long fill_textconv (struct repository*,struct userdiff_driver*,struct diff_filespec*,char**) ; 
 int /*<<< orphan*/  free_filespec (struct diff_filespec*) ; 
 struct userdiff_driver* get_textconv (struct repository*,struct diff_filespec*) ; 

int textconv_object(struct repository *r,
		    const char *path,
		    unsigned mode,
		    const struct object_id *oid,
		    int oid_valid,
		    char **buf,
		    unsigned long *buf_size)
{
	struct diff_filespec *df;
	struct userdiff_driver *textconv;

	df = alloc_filespec(path);
	fill_filespec(df, oid, oid_valid, mode);
	textconv = get_textconv(r, df);
	if (!textconv) {
		free_filespec(df);
		return 0;
	}

	*buf_size = fill_textconv(r, textconv, df, buf);
	free_filespec(df);
	return 1;
}