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
struct ber {scalar_t__ br_wptr; scalar_t__ br_wend; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,scalar_t__,size_t) ; 

__attribute__((used)) static void
ber_write(struct ber *ber, void *buf, size_t len)
{
	if (ber->br_wptr + len <= ber->br_wend)
		bcopy(buf, ber->br_wptr, len);
	ber->br_wptr += len;
}