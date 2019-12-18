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
struct rtas_error_log {int dummy; } ;
struct TYPE_2__ {scalar_t__ mce_data_buf; } ;

/* Variables and functions */
 TYPE_1__* local_paca ; 

__attribute__((used)) static inline struct rtas_error_log *fwnmi_get_errlog(void)
{
	return (struct rtas_error_log *)local_paca->mce_data_buf;
}