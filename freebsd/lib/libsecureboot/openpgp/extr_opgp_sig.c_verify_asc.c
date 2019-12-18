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
typedef  int /*<<< orphan*/  pbuf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ openpgp_verify (char*,unsigned char*,size_t,unsigned char*,size_t,int) ; 
 unsigned char* read_file (char const*,size_t*) ; 
 size_t strlcpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

unsigned char *
verify_asc(const char *sigfile, int flags)
{
	char pbuf[MAXPATHLEN];
	char *cp;
	size_t n;
	unsigned char *fdata, *sdata;
	size_t fbytes, sbytes;
    
	if ((sdata = read_file(sigfile, &sbytes))) {
		n = strlcpy(pbuf, sigfile, sizeof(pbuf));
		if ((cp = strrchr(pbuf, '.')))
			*cp = '\0';
		if ((fdata = read_file(pbuf, &fbytes))) {
			if (openpgp_verify(pbuf, fdata, fbytes, sdata,
				sbytes, flags)) {
				free(fdata);
				fdata = NULL;
			}
		}
	} else
		fdata = NULL;
	free(sdata);
	return (fdata);
}