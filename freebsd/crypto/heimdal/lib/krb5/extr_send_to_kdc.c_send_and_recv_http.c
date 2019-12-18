#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
struct TYPE_7__ {char* data; int length; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_get_int (char*,unsigned long*,int) ; 
 int asprintf (char**,char*,char const*,char*) ; 
 int base64_encode (char*,int,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned long) ; 
 int net_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* realloc (char*,int) ; 
 int recv_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int
send_and_recv_http(krb5_socket_t fd,
		   time_t tmout,
		   const char *prefix,
		   const krb5_data *req,
		   krb5_data *rep)
{
    char *request = NULL;
    char *str;
    int ret;
    int len = base64_encode(req->data, req->length, &str);

    if(len < 0)
	return -1;
    ret = asprintf(&request, "GET %s%s HTTP/1.0\r\n\r\n", prefix, str);
    free(str);
    if (ret < 0 || request == NULL)
	return -1;
    ret = net_write (fd, request, strlen(request));
    free (request);
    if (ret < 0)
	return ret;
    ret = recv_loop(fd, tmout, 0, 0, rep);
    if(ret)
	return ret;
    {
	unsigned long rep_len;
	char *s, *p;

	s = realloc(rep->data, rep->length + 1);
	if (s == NULL) {
	    krb5_data_free (rep);
	    return -1;
	}
	s[rep->length] = 0;
	p = strstr(s, "\r\n\r\n");
	if(p == NULL) {
	    krb5_data_zero(rep);
	    free(s);
	    return -1;
	}
	p += 4;
	rep->data = s;
	rep->length -= p - s;
	if(rep->length < 4) { /* remove length */
	    krb5_data_zero(rep);
	    free(s);
	    return -1;
	}
	rep->length -= 4;
	_krb5_get_int(p, &rep_len, 4);
	if (rep_len != rep->length) {
	    krb5_data_zero(rep);
	    free(s);
	    return -1;
	}
	memmove(rep->data, p + 4, rep->length);
    }
    return 0;
}