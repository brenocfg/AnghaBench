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
struct TYPE_3__ {scalar_t__ l_buf; } ;
typedef  TYPE_1__ kurl_t ;

/* Variables and functions */

int kurl_eof(const kurl_t *ku)
{
	if (ku == 0) return 1;
	return (ku->l_buf == 0); // unless file end, buffer should never be empty
}