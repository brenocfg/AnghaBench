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
 int /*<<< orphan*/  ASN1_F_DO_CREATE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int NID_undef ; 
 int OBJ_create (char const*,char const*,char const*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ ossl_isspace (char const) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int do_create(const char *value, const char *name)
{
    int nid;
    const char *ln, *ostr, *p;
    char *lntmp = NULL;

    p = strrchr(value, ',');
    if (p == NULL) {
        ln = name;
        ostr = value;
    } else {
        ln = value;
        ostr = p + 1;
        if (*ostr == '\0')
            return 0;
        while (ossl_isspace(*ostr))
            ostr++;
        while (ossl_isspace(*ln))
            ln++;
        p--;
        while (ossl_isspace(*p)) {
            if (p == ln)
                return 0;
            p--;
        }
        p++;
        if ((lntmp = OPENSSL_malloc((p - ln) + 1)) == NULL) {
            ASN1err(ASN1_F_DO_CREATE, ERR_R_MALLOC_FAILURE);
            return 0;
        }
        memcpy(lntmp, ln, p - ln);
        lntmp[p - ln] = '\0';
        ln = lntmp;
    }

    nid = OBJ_create(ostr, name, ln);

    OPENSSL_free(lntmp);

    return nid != NID_undef;
}