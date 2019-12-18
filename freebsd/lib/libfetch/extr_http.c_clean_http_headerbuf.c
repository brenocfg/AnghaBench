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
struct TYPE_4__ {scalar_t__ buf; } ;
typedef  TYPE_1__ http_headerbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  init_http_headerbuf (TYPE_1__*) ; 

__attribute__((used)) static void
clean_http_headerbuf(http_headerbuf_t *buf)
{
	if (buf->buf)
		free(buf->buf);
	init_http_headerbuf(buf);
}