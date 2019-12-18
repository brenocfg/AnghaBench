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
typedef  int xo_ssize_t ;
struct TYPE_3__ {char* xb_curp; } ;
typedef  TYPE_1__ xo_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int xo_buf_left (TYPE_1__*) ; 

__attribute__((used)) static xo_ssize_t
xo_syslog_handle_write (void *opaque, const char *data)
{
    xo_buffer_t *xbp = opaque;
    int len = strlen(data);
    int left = xo_buf_left(xbp);

    if (len > left - 1)
	len = left - 1;

    memcpy(xbp->xb_curp, data, len);
    xbp->xb_curp += len;
    *xbp->xb_curp = '\0';

    return len;
}