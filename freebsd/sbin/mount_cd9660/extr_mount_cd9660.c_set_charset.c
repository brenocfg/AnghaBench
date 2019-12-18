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
 int /*<<< orphan*/  ENCODING_UNICODE ; 
 int /*<<< orphan*/  ICONV_CSNMAXLEN ; 
 int /*<<< orphan*/  KICONV_VENDOR_MICSFT ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int kiconv_add_xlat16_cspairs (char*,char*) ; 
 int /*<<< orphan*/  kiconv_quirkcs (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ kldload (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
set_charset(struct iovec **iov, int *iovlen, const char *localcs)
{
	int error;
	char *cs_disk;	/* disk charset for Joliet cs conversion */
	char *cs_local;	/* local charset for Joliet cs conversion */

	cs_disk = NULL;
	cs_local = NULL;

	if (modfind("cd9660_iconv") < 0)
		if (kldload("cd9660_iconv") < 0 || modfind("cd9660_iconv") < 0) {
			warnx( "cannot find or load \"cd9660_iconv\" kernel module");
			return (-1);
		}

	if ((cs_disk = malloc(ICONV_CSNMAXLEN)) == NULL)
		return (-1);
	if ((cs_local = malloc(ICONV_CSNMAXLEN)) == NULL) {
		free(cs_disk);
		return (-1);
	}
	strncpy(cs_disk, ENCODING_UNICODE, ICONV_CSNMAXLEN);
	strncpy(cs_local, kiconv_quirkcs(localcs, KICONV_VENDOR_MICSFT),
	    ICONV_CSNMAXLEN);
	error = kiconv_add_xlat16_cspairs(cs_disk, cs_local);
	if (error)
		return (-1);
	
	build_iovec(iov, iovlen, "cs_disk", cs_disk, (size_t)-1);
	build_iovec(iov, iovlen, "cs_local", cs_local, (size_t)-1);

	return (0);
}