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
struct dmaengine_desc_callback {scalar_t__ callback; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
dmaengine_desc_callback_valid(struct dmaengine_desc_callback *cb)
{
	return (cb->callback) ? true : false;
}