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
struct package {int pkg_fd; int /*<<< orphan*/  pkg_zs; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int COMMENT ; 
 int EFTYPE ; 
 int ENOMEM ; 
 int EXTRA_FIELD ; 
 int HEAD_CRC ; 
 int ORIG_NAME ; 
 int RESERVED ; 
 int Z_DEFLATED ; 
 int Z_OK ; 
 int /*<<< orphan*/  bzero (struct package*,int) ; 
 int /*<<< orphan*/  free (struct package*) ; 
 int get_byte (struct package*,scalar_t__*) ; 
 int inflateInit2 (int /*<<< orphan*/ *,int) ; 
 struct package* malloc (int) ; 
 int /*<<< orphan*/  putchar (int) ; 

__attribute__((used)) static int
new_package(int fd, struct package **pp)
{
	struct package *pkg;
	off_t ofs;
	int flags, i, error;

	pkg = malloc(sizeof(*pkg));
	if (pkg == NULL)
		return (ENOMEM);

	bzero(pkg, sizeof(*pkg));
	pkg->pkg_fd = fd;

	/*
	 * Parse the header.
	 */
	error = EFTYPE;
	ofs = 0;

	/* Check megic. */
	if (get_byte(pkg, &ofs) != 0x1f || get_byte(pkg, &ofs) != 0x8b)
		goto fail;
	/* Check method. */
	if (get_byte(pkg, &ofs) != Z_DEFLATED)
		goto fail;
	/* Check flags. */
	flags = get_byte(pkg, &ofs);
	if (flags & RESERVED)
		goto fail;

	/* Skip time, xflags and OS code. */
	for (i = 0; i < 6; i++) {
		if (get_byte(pkg, &ofs) == -1)
			goto fail;
	}

	/* Skip extra field. */
	if (flags & EXTRA_FIELD) {
		i = (get_byte(pkg, &ofs) & 0xff) |
		    ((get_byte(pkg, &ofs) << 8) & 0xff);
		while (i-- > 0) {
			if (get_byte(pkg, &ofs) == -1)
				goto fail;
		}
	}

	/* Skip original file name. */
	if (flags & ORIG_NAME) {
		do {
			i = get_byte(pkg, &ofs);
		} while (i != 0 && i != -1);
		if (i == -1)
			goto fail;
	}

	/* Print the comment if it's there. */
	if (flags & COMMENT) {
		while (1) {
			i = get_byte(pkg, &ofs);
			if (i == -1)
				goto fail;
			if (i == 0)
				break;
			putchar(i);
		}
	}

	/* Skip the CRC. */
	if (flags & HEAD_CRC) {
		if (get_byte(pkg, &ofs) == -1)
			goto fail;
		if (get_byte(pkg, &ofs) == -1)
			goto fail;
	}

	/*
	 * Done parsing the ZIP header. Spkgt the inflation engine.
	 */
	error = inflateInit2(&pkg->pkg_zs, -15);
	if (error != Z_OK)
		goto fail;

	*pp = pkg;
	return (0);

 fail:
	free(pkg);
	return (error);
}