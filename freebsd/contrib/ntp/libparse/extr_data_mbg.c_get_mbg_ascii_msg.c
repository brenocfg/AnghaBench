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
struct TYPE_3__ {int /*<<< orphan*/  s; int /*<<< orphan*/  valid; scalar_t__ csum; } ;
typedef  scalar_t__ CSUM ;
typedef  TYPE_1__ ASCII_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 scalar_t__ get_lsb_short (unsigned char**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

void
get_mbg_ascii_msg(
	unsigned char **bufpp,
	ASCII_MSG *ascii_msgp
	)
{
  ascii_msgp->csum  = (CSUM) get_lsb_short(bufpp);
  ascii_msgp->valid = get_lsb_int16(bufpp);
  memcpy(ascii_msgp->s, *bufpp, sizeof(ascii_msgp->s));
  *bufpp += sizeof(ascii_msgp->s);
}