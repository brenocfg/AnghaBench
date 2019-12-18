#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  kadm5_ret_t ;
struct TYPE_9__ {TYPE_1__* socket_info; int /*<<< orphan*/  version; int /*<<< orphan*/  socket_fd; int /*<<< orphan*/  socket_name; int /*<<< orphan*/  log_fd; } ;
typedef  TYPE_3__ kadm5_log_context ;
struct TYPE_7__ {int ai_addrlen; struct sockaddr* ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sendto (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static kadm5_ret_t
kadm5_log_flush (kadm5_log_context *log_context,
		 krb5_storage *sp)
{
    krb5_data data;
    size_t len;
    ssize_t ret;

    krb5_storage_to_data(sp, &data);
    len = data.length;
    ret = write (log_context->log_fd, data.data, len);
    if (ret < 0 || (size_t)ret != len) {
	krb5_data_free(&data);
	return errno;
    }
    if (fsync (log_context->log_fd) < 0) {
	krb5_data_free(&data);
	return errno;
    }

    /*
     * Try to send a signal to any running `ipropd-master'
     */
#ifndef NO_UNIX_SOCKETS
    sendto (log_context->socket_fd,
	    (void *)&log_context->version,
	    sizeof(log_context->version),
	    0,
	    (struct sockaddr *)&log_context->socket_name,
	    sizeof(log_context->socket_name));
#else
    sendto (log_context->socket_fd,
	    (void *)&log_context->version,
	    sizeof(log_context->version),
	    0,
	    log_context->socket_info->ai_addr,
	    log_context->socket_info->ai_addrlen);
#endif

    krb5_data_free(&data);
    return 0;
}