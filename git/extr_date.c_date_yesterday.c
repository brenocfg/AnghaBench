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
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_tm (struct tm*,struct tm*,int) ; 

__attribute__((used)) static void date_yesterday(struct tm *tm, struct tm *now, int *num)
{
	*num = 0;
	update_tm(tm, now, 24*60*60);
}