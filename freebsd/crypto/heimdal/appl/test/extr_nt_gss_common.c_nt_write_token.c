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
struct TYPE_4__ {int length; unsigned char* value; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int write (int,unsigned char*,int) ; 

void
nt_write_token (int sock, gss_buffer_t buf)
{
    unsigned char net_len[4];
    uint32_t len;
    OM_uint32 min_stat;

    len = buf->length;

    net_len[0] = (len >>  0) & 0xFF;
    net_len[1] = (len >>  8) & 0xFF;
    net_len[2] = (len >> 16) & 0xFF;
    net_len[3] = (len >> 24) & 0xFF;

    if (write (sock, net_len, 4) != 4)
	err (1, "write");
    if (write (sock, buf->value, len) != len)
	err (1, "write");

    gss_release_buffer (&min_stat, buf);
}