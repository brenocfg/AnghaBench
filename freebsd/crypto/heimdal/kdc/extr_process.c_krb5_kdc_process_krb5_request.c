#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int krb5_error_code ;
struct TYPE_6__ {unsigned char* data; size_t length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {int (* process ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char const*,struct sockaddr*,int,int*) ;int flags; } ;

/* Variables and functions */
 int KS_KRB5 ; 
 TYPE_4__* services ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,char const*,struct sockaddr*,int,int*) ; 

int
krb5_kdc_process_krb5_request(krb5_context context,
			      krb5_kdc_configuration *config,
			      unsigned char *buf,
			      size_t len,
			      krb5_data *reply,
			      const char *from,
			      struct sockaddr *addr,
			      int datagram_reply)
{
    krb5_error_code ret;
    unsigned int i;
    krb5_data req_buffer;
    int claim = 0;

    req_buffer.data = buf;
    req_buffer.length = len;

    for (i = 0; services[i].process != NULL; i++) {
	if ((services[i].flags & KS_KRB5) == 0)
	    continue;
	ret = (*services[i].process)(context, config, &req_buffer,
				     reply, from, addr, datagram_reply,
				     &claim);
	if (claim)
	    return ret;
    }

    return -1;
}