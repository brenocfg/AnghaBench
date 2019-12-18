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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int16_t ;
typedef  char* heim_general_string ;

/* Variables and functions */
 int ENOMEM ; 
 int KRB5_KT_END ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int errno ; 
 int krb5_ret_int16 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int krb5_storage_read (int /*<<< orphan*/ *,char*,int) ; 
 char* malloc (int) ; 

__attribute__((used)) static krb5_error_code
krb5_kt_ret_string(krb5_context context,
		   krb5_storage *sp,
		   heim_general_string *data)
{
    int ret;
    int16_t size;
    ret = krb5_ret_int16(sp, &size);
    if(ret)
	return ret;
    *data = malloc(size + 1);
    if (*data == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    ret = krb5_storage_read(sp, *data, size);
    (*data)[size] = '\0';
    if(ret != size)
	return (ret < 0)? errno : KRB5_KT_END;
    return 0;
}