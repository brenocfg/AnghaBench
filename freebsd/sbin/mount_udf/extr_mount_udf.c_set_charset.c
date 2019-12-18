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

/* Variables and functions */
 char const* ENCODING_UNICODE ; 
 int /*<<< orphan*/  ICONV_CSNMAXLEN ; 
 int kiconv_add_xlat16_cspairs (char*,char*) ; 
 scalar_t__ kldload (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
set_charset(char **cs_disk, char **cs_local, const char *localcs)
{
	int error;

	if (modfind("udf_iconv") < 0)
		if (kldload("udf_iconv") < 0 || modfind("udf_iconv") < 0) {
			warnx( "cannot find or load \"udf_iconv\" kernel module");
			return (-1);
		}

	if ((*cs_disk = malloc(ICONV_CSNMAXLEN)) == NULL)
		return (-1);
	if ((*cs_local = malloc(ICONV_CSNMAXLEN)) == NULL)
		return (-1);
	strncpy(*cs_disk, ENCODING_UNICODE, ICONV_CSNMAXLEN);
	strncpy(*cs_local, localcs, ICONV_CSNMAXLEN);
	error = kiconv_add_xlat16_cspairs(*cs_disk, *cs_local);
	if (error)
		return (-1);

	return (0);
}