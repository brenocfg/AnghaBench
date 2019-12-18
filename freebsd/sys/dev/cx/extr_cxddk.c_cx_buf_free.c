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
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATBSTS (int /*<<< orphan*/ ) ; 
 int BSTS_OWN24 ; 
 int /*<<< orphan*/  BTBSTS (int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 

int cx_buf_free (cx_chan_t *c)
{
	return ! (inb (ATBSTS(c->port)) & BSTS_OWN24) +
		! (inb (BTBSTS(c->port)) & BSTS_OWN24);
}