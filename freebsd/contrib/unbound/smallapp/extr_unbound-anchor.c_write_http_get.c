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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 char const* PACKAGE_VERSION ; 
 scalar_t__ write_ssl_line (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int
write_http_get(SSL* ssl, const char* pathname, const char* urlname)
{
	if(write_ssl_line(ssl, "GET /%s HTTP/1.1", pathname) &&
	   write_ssl_line(ssl, "Host: %s", urlname) &&
	   write_ssl_line(ssl, "User-Agent: unbound-anchor/%s",
	   	PACKAGE_VERSION) &&
	   /* We do not really do multiple queries per connection,
	    * but this header setting is also not needed.
	    * write_ssl_line(ssl, "Connection: close", NULL) &&*/
	   write_ssl_line(ssl, "", NULL)) {
		return 1;
	}
	return 0;
}