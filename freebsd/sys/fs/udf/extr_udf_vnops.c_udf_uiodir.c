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
struct uio {int uio_resid; } ;
struct udf_uiodir {scalar_t__ acookies; scalar_t__ ncookies; int /*<<< orphan*/  dirent; scalar_t__ eofflag; int /*<<< orphan*/ * cookies; } ;

/* Variables and functions */
 int uiomove (int /*<<< orphan*/ ,int,struct uio*) ; 

__attribute__((used)) static int
udf_uiodir(struct udf_uiodir *uiodir, int de_size, struct uio *uio, long cookie)
{
	if (uiodir->cookies != NULL) {
		if (++uiodir->acookies > uiodir->ncookies) {
			uiodir->eofflag = 0;
			return (-1);
		}
		*uiodir->cookies++ = cookie;
	}

	if (uio->uio_resid < de_size) {
		uiodir->eofflag = 0;
		return (-1);
	}

	return (uiomove(uiodir->dirent, de_size, uio));
}