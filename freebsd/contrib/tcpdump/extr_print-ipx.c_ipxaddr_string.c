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
typedef  int uint32_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int const,int const,int const,int const,int const,int const) ; 

__attribute__((used)) static const char *
ipxaddr_string(uint32_t net, const u_char *node)
{
    static char line[256];

    snprintf(line, sizeof(line), "%08x.%02x:%02x:%02x:%02x:%02x:%02x",
	    net, node[0], node[1], node[2], node[3], node[4], node[5]);

    return line;
}