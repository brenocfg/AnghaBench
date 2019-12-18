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
struct TYPE_3__ {int mode; int /*<<< orphan*/  saved_r0; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void bpck_disconnect ( PIA *pi )

{	w0(0); 
	if (pi->mode >= 2) { w2(9); w2(0); } else t2(2);
	w2(0x4c); w0(pi->saved_r0);
}