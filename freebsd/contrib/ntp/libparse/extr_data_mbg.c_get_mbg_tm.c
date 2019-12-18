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
struct TYPE_3__ {int /*<<< orphan*/  status; void* offs_from_utc; void* frac; int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  wday; void* yday; int /*<<< orphan*/  mday; int /*<<< orphan*/  month; void* year; } ;
typedef  TYPE_1__ TM_GPS ;

/* Variables and functions */
 void* get_lsb_int16 (unsigned char**) ; 
 void* get_lsb_long (unsigned char**) ; 
 int /*<<< orphan*/  get_lsb_uint16 (unsigned char**) ; 

void
get_mbg_tm(
	unsigned char **buffpp,
	TM_GPS *tmp
	)
{
  tmp->year = get_lsb_int16(buffpp);
  tmp->month = *(*buffpp)++;
  tmp->mday = *(*buffpp)++;
  tmp->yday = get_lsb_int16(buffpp);
  tmp->wday = *(*buffpp)++;
  tmp->hour = *(*buffpp)++;
  tmp->min = *(*buffpp)++;
  tmp->sec = *(*buffpp)++;
  tmp->frac = get_lsb_long(buffpp);
  tmp->offs_from_utc = get_lsb_long(buffpp);
  tmp->status = get_lsb_uint16(buffpp);
}