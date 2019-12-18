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
typedef  int boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_hdr; } ;
typedef  TYPE_1__ arc_buf_t ;

/* Variables and functions */
 scalar_t__ HDR_ISTYPE_METADATA (int /*<<< orphan*/ ) ; 

boolean_t
arc_is_metadata(arc_buf_t *buf)
{
	return (HDR_ISTYPE_METADATA(buf->b_hdr) != 0);
}