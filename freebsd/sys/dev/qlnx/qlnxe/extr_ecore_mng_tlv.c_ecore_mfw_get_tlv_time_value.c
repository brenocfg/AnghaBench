#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ecore_tlv_parsed_buf {int /*<<< orphan*/  data; int /*<<< orphan*/  p_val; } ;
struct ecore_mfw_tlv_time {int month; int day; int hour; int min; int msec; int usec; int /*<<< orphan*/  b_set; } ;

/* Variables and functions */
 int ECORE_TLV_DATA_MAX ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_SNPRINTF (int /*<<< orphan*/ ,int,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
ecore_mfw_get_tlv_time_value(struct ecore_mfw_tlv_time *p_time,
			     struct ecore_tlv_parsed_buf *p_buf)
{
	if (!p_time->b_set)
		return -1;

	/* Validate numbers */
	if (p_time->month > 12)
		p_time->month = 0;
	if (p_time->day > 31)
		p_time->day = 0;
	if (p_time->hour > 23)
		p_time->hour = 0;
	if (p_time->min > 59)
		p_time->hour = 0;
	if (p_time->msec > 999)
		p_time->msec = 0;
	if (p_time->usec > 999)
		p_time->usec = 0;

	OSAL_MEM_ZERO(p_buf->data, sizeof(u8) * ECORE_TLV_DATA_MAX);
	OSAL_SNPRINTF(p_buf->data, 14, "%d%d%d%d%d%d",
		      p_time->month, p_time->day,
		      p_time->hour, p_time->min,
		      p_time->msec, p_time->usec);

	p_buf->p_val = p_buf->data;
	return 14;
}