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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  PACKAGE_VERSION ; 
 scalar_t__ sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
setup_http_request(sldns_buffer* buf, char* host, char* path)
{
	sldns_buffer_clear(buf);
	sldns_buffer_printf(buf, "GET /%s HTTP/1.1\r\n", path);
	sldns_buffer_printf(buf, "Host: %s\r\n", host);
	sldns_buffer_printf(buf, "User-Agent: unbound/%s\r\n",
		PACKAGE_VERSION);
	/* We do not really do multiple queries per connection,
	 * but this header setting is also not needed.
	 * sldns_buffer_printf(buf, "Connection: close\r\n") */
	sldns_buffer_printf(buf, "\r\n");
	if(sldns_buffer_position(buf)+10 > sldns_buffer_capacity(buf))
		return 0; /* somehow buffer too short, but it is about 60K
		and the request is only a couple bytes long. */
	sldns_buffer_flip(buf);
	return 1;
}