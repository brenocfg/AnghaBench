#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {long race_result; } ;

/* Variables and functions */
 scalar_t__ get_tb () ; 
 TYPE_1__* tbsync ; 

__attribute__((used)) static void enter_contest(u64 mark, long add)
{
	while (get_tb() < mark)
		tbsync->race_result = add;
}