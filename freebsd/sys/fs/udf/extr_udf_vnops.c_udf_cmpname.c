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
struct udf_mnt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int bcmp (char*,char*,int) ; 
 int udf_transname (char*,char*,int,struct udf_mnt*) ; 
 int /*<<< orphan*/  udf_zone_trans ; 
 char* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
udf_cmpname(char *cs0string, char *cmpname, int cs0len, int cmplen, struct udf_mnt *udfmp)
{
	char *transname;
	int error = 0;

	/* This is overkill, but not worth creating a new zone */
	transname = uma_zalloc(udf_zone_trans, M_WAITOK);

	cs0len = udf_transname(cs0string, transname, cs0len, udfmp);

	/* Easy check.  If they aren't the same length, they aren't equal */
	if ((cs0len == 0) || (cs0len != cmplen))
		error = -1;
	else
		error = bcmp(transname, cmpname, cmplen);

	uma_zfree(udf_zone_trans, transname);
	return (error);
}