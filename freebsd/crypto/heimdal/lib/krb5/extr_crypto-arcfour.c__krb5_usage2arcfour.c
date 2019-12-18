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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
#define  KRB5_KU_AS_REP_ENC_PART 131 
#define  KRB5_KU_USAGE_SEAL 130 
#define  KRB5_KU_USAGE_SEQ 129 
#define  KRB5_KU_USAGE_SIGN 128 

krb5_error_code
_krb5_usage2arcfour(krb5_context context, unsigned *usage)
{
    switch (*usage) {
    case KRB5_KU_AS_REP_ENC_PART : /* 3 */
	*usage = 8;
	return 0;
    case KRB5_KU_USAGE_SEAL :  /* 22 */
	*usage = 13;
	return 0;
    case KRB5_KU_USAGE_SIGN : /* 23 */
        *usage = 15;
        return 0;
    case KRB5_KU_USAGE_SEQ: /* 24 */
	*usage = 0;
	return 0;
    default :
	return 0;
    }
}