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
typedef  TYPE_1__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSR (int /*<<< orphan*/ ) ; 
 int BSR_NOINTR ; 
 int inw (int /*<<< orphan*/ ) ; 

int cx_checkintr (cx_board_t *b)
{
	return (!(inw (BSR(b->port)) & BSR_NOINTR));
}