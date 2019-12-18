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
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 char const* ENCODING_UNICODE ; 
 int KICONV_FROM_UPPER ; 
 int KICONV_LOWER ; 
 int /*<<< orphan*/  build_iovec_argf (struct iovec**,int*,char*,char const*) ; 
 scalar_t__ errno ; 
 int kiconv_add_xlat16_cspair (char const*,char const*,int) ; 
 int kiconv_add_xlat16_cspairs (char const*,char const*) ; 
 scalar_t__ kldload (char*) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
set_charset(struct iovec **iov, int *iovlen, const char *cs_local, const char *cs_dos)
{
	int error;

	if (modfind("msdosfs_iconv") < 0)
		if (kldload("msdosfs_iconv") < 0 || modfind("msdosfs_iconv") < 0) {
			warnx("cannot find or load \"msdosfs_iconv\" kernel module");
			return (-1);
		}

	build_iovec_argf(iov, iovlen, "cs_win", ENCODING_UNICODE);
	error = kiconv_add_xlat16_cspairs(ENCODING_UNICODE, cs_local);
	if (error && errno != EEXIST)
		return (-1);
	if (cs_dos != NULL) {
		error = kiconv_add_xlat16_cspairs(cs_dos, cs_local);
		if (error && errno != EEXIST)
			return (-1);
	} else {
		build_iovec_argf(iov, iovlen, "cs_dos", cs_local);
		error = kiconv_add_xlat16_cspair(cs_local, cs_local,
				KICONV_FROM_UPPER | KICONV_LOWER);
		if (error && errno != EEXIST)
			return (-1);
	}

	return (0);
}