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
struct TYPE_4__ {size_t clen; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  ARG_CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  v_key_name (TYPE_1__*,int /*<<< orphan*/ ) ; 

size_t
v_key_len(
	SCR *sp,
	ARG_CHAR_T ch)
{
	(void)v_key_name(sp, ch);
	return (sp->clen);
}