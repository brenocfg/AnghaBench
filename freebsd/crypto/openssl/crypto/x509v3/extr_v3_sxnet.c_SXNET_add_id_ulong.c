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
typedef  int /*<<< orphan*/  SXNET ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int SXNET_add_id_INTEGER (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  X509V3_F_SXNET_ADD_ID_ULONG ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SXNET_add_id_ulong(SXNET **psx, unsigned long lzone, const char *user,
                       int userlen)
{
    ASN1_INTEGER *izone;

    if ((izone = ASN1_INTEGER_new()) == NULL
        || !ASN1_INTEGER_set(izone, lzone)) {
        X509V3err(X509V3_F_SXNET_ADD_ID_ULONG, ERR_R_MALLOC_FAILURE);
        ASN1_INTEGER_free(izone);
        return 0;
    }
    return SXNET_add_id_INTEGER(psx, izone, user, userlen);

}