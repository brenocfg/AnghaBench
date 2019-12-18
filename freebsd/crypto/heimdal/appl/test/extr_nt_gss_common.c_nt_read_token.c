#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int length; unsigned char* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned char* malloc (int) ; 
 int read (int,unsigned char*,int) ; 

void
nt_read_token (int sock, gss_buffer_t buf)
{
    unsigned char net_len[4];
    uint32_t len;

    if (read(sock, net_len, 4) != 4)
	err (1, "read");
    len = (net_len[0] <<  0)
	| (net_len[1] <<  8)
	| (net_len[2] << 16)
	| (net_len[3] << 24);

    buf->length = len;
    buf->value  = malloc(len);
    if (read (sock, buf->value, len) != len)
	err (1, "read");
}