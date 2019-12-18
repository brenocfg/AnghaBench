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
struct TYPE_3__ {int /*<<< orphan*/  delta_t; int /*<<< orphan*/  tm_reconn; int /*<<< orphan*/  tm_disconn; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ ANT_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 int /*<<< orphan*/  get_lsb_long (unsigned char**) ; 
 int /*<<< orphan*/  get_mbg_tm (unsigned char**,int /*<<< orphan*/ *) ; 

void
get_mbg_antinfo(
	unsigned char **buffpp,
	ANT_INFO *antinfop
	)
{
  antinfop->status = get_lsb_int16(buffpp);
  get_mbg_tm(buffpp, &antinfop->tm_disconn);
  get_mbg_tm(buffpp, &antinfop->tm_reconn);
  antinfop->delta_t = get_lsb_long(buffpp);
}