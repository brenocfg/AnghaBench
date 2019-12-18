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
struct TYPE_3__ {int buflen; char* buf; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static void
http_conn_trimright(conn_t *conn)
{
	while (conn->buflen &&
	       isspace((unsigned char)conn->buf[conn->buflen - 1]))
		conn->buflen--;
	conn->buf[conn->buflen] = '\0';
}