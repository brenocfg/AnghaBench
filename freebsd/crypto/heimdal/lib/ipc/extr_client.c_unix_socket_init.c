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
 int common_path_init (char const*,char*,void**) ; 
 int /*<<< orphan*/  common_release (void*) ; 
 int connect_unix (void*) ; 

__attribute__((used)) static int
unix_socket_init(const char *service,
		 void **ctx)
{
    int ret;

    ret = common_path_init(service, "socket", ctx);
    if (ret)
	return ret;
    ret = connect_unix(*ctx);
    if (ret)
	common_release(*ctx);

    return ret;
}