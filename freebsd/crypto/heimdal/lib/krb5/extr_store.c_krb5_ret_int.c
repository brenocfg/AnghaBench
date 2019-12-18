#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* fetch ) (TYPE_1__*,unsigned char*,size_t) ;int /*<<< orphan*/  eof_code; } ;
typedef  TYPE_1__ krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  unsigned long int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_get_int (unsigned char*,unsigned long*,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int stub1 (TYPE_1__*,unsigned char*,size_t) ; 

__attribute__((used)) static krb5_error_code
krb5_ret_int(krb5_storage *sp,
	     int32_t *value,
	     size_t len)
{
    int ret;
    unsigned char v[4];
    unsigned long w;
    ret = sp->fetch(sp, v, len);
    if (ret < 0)
	return errno;
    if ((size_t)ret != len)
	return sp->eof_code;
    _krb5_get_int(v, &w, len);
    *value = w;
    return 0;
}