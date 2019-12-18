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
struct tbl_dat {char* string; } ;
struct rofftbl {size_t (* slen ) (char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg; } ;
struct roffcol {size_t width; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 char* mandoc_strdup (char*) ; 
 char* strchr (char const*,char) ; 
 size_t stub1 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
tblcalc_literal(struct rofftbl *tbl, struct roffcol *col,
    const struct tbl_dat *dp, size_t mw)
{
	const char	*str;	/* Beginning of the first line. */
	const char	*beg;	/* Beginning of the current line. */
	char		*end;	/* End of the current line. */
	size_t		 lsz;	/* Length of the current line. */
	size_t		 wsz;	/* Length of the current word. */
	size_t		 msz;   /* Length of the longest line. */

	if (dp->string == NULL || *dp->string == '\0')
		return 0;
	str = mw ? mandoc_strdup(dp->string) : dp->string;
	msz = lsz = 0;
	for (beg = str; beg != NULL && *beg != '\0'; beg = end) {
		end = mw ? strchr(beg, ' ') : NULL;
		if (end != NULL) {
			*end++ = '\0';
			while (*end == ' ')
				end++;
		}
		wsz = (*tbl->slen)(beg, tbl->arg);
		if (mw && lsz && lsz + 1 + wsz <= mw)
			lsz += 1 + wsz;
		else
			lsz = wsz;
		if (msz < lsz)
			msz = lsz;
	}
	if (mw)
		free((void *)str);
	if (col != NULL && col->width < msz)
		col->width = msz;
	return msz;
}