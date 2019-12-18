#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_char ;
struct msdosfsmount {int pm_flags; int /*<<< orphan*/  pm_d2u; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* convchr ) (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ;int /*<<< orphan*/  (* convchr_case ) (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KICONV_LOWER ; 
 int LCASE_BASE ; 
 int LCASE_EXT ; 
 int MSDOSFSMNT_KICONV ; 
 size_t* dos2unix ; 
 TYPE_1__* msdosfs_iconv ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const**,size_t*,char**,size_t*) ; 
 size_t* u2l ; 

__attribute__((used)) static u_char *
dos2unixchr(u_char *outbuf, const u_char **instr, size_t *ilen, int lower, struct msdosfsmount *pmp)
{
	u_char c, *outp;
	size_t len, olen;

	outp = outbuf;
	if (pmp->pm_flags & MSDOSFSMNT_KICONV && msdosfs_iconv) {
		olen = len = 4;

		if (lower & (LCASE_BASE | LCASE_EXT))
			msdosfs_iconv->convchr_case(pmp->pm_d2u, (const char **)instr,
						  ilen, (char **)&outp, &olen, KICONV_LOWER);
		else
			msdosfs_iconv->convchr(pmp->pm_d2u, (const char **)instr,
					     ilen, (char **)&outp, &olen);
		len -= olen;

		/*
		 * return '?' if failed to convert
		 */
		if (len == 0) {
			(*ilen)--;
			(*instr)++;
			*outp++ = '?';
		}
	} else {
		(*ilen)--;
		c = *(*instr)++;
		c = dos2unix[c];
		if (lower & (LCASE_BASE | LCASE_EXT))
			c = u2l[c];
		*outp++ = c;
		outbuf[1] = '\0';
	}

	*outp = '\0';
	outp = outbuf;
	return (outp);
}