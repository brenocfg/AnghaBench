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
struct sge_fl {scalar_t__ credits; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  refill_fl (int /*<<< orphan*/ *,struct sge_fl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
__refill_fl(adapter_t *adap, struct sge_fl *fl)
{
	refill_fl(adap, fl, min(16U, fl->size - fl->credits));
}