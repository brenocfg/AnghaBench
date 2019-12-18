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
struct TYPE_3__ {scalar_t__ buflen; scalar_t__ bufsize; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ http_headerbuf_t ;

/* Variables and functions */

__attribute__((used)) static void
init_http_headerbuf(http_headerbuf_t *buf)
{
	buf->buf = NULL;
	buf->bufsize = 0;
	buf->buflen = 0;
}