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
struct TYPE_2__ {size_t context_len; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 size_t MIN (int,size_t) ; 
 TYPE_1__* lm ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

void mumble_set_context(const unsigned char* context, size_t len)
{
	if (!lm)
		return;
	len = MIN(sizeof(lm->context), len);
	lm->context_len = len;
	memcpy(lm->context, context, len);
}