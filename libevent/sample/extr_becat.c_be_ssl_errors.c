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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 char* ERR_func_error_string (int) ; 
 char* ERR_lib_error_string (int) ; 
 char* ERR_reason_error_string (int) ; 
 int bufferevent_get_openssl_error (struct bufferevent*) ; 
 int /*<<< orphan*/  error (char*,int,char const*,char const*,char const*) ; 

__attribute__((used)) static void be_ssl_errors(struct bufferevent *bev)
{
	int err;
	while ((err = bufferevent_get_openssl_error(bev))) {
		const char *msg = ERR_reason_error_string(err);
		const char *lib = ERR_lib_error_string(err);
		const char *func = ERR_func_error_string(err);
		error("ssl/err=%d/%s in %s %s\n", err, msg, lib, func);
	}
}