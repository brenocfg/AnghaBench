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
typedef  int /*<<< orphan*/  xo_buffer_t ;
struct TYPE_3__ {int c_flags; } ;
typedef  TYPE_1__ csv_private_t ;

/* Variables and functions */
 int CF_DOS_NEWLINE ; 
 int /*<<< orphan*/  xo_buf_append (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
csv_append_newline (xo_buffer_t *xbp, csv_private_t *csv)
{
    if (csv->c_flags & CF_DOS_NEWLINE)
	xo_buf_append(xbp, "\r\n", 2);
    else 
	xo_buf_append(xbp, "\n", 1);
}