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
typedef  int uint32_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_4__ {int length; int* value; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int htonl (int) ; 
 int net_write (int,int*,int) ; 

void
write_token (int sock, gss_buffer_t buf)
{
    uint32_t len, net_len;
    OM_uint32 min_stat;

    len = buf->length;

    net_len = htonl(len);

    if (net_write (sock, &net_len, 4) != 4)
	err (1, "write");
    if (net_write (sock, buf->value, len) != len)
	err (1, "write");

    gss_release_buffer (&min_stat, buf);
}