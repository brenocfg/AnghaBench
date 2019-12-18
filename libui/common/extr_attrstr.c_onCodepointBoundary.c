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
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__* s; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */

__attribute__((used)) static int onCodepointBoundary(uiAttributedString *s, size_t at)
{
	uint8_t c;

	// for uiNewAttributedString()
	if (s->s == NULL && at == 0)
		return 1;
	c = (uint8_t) (s->s[at]);
	return c < 0x80 || c >= 0xC0;
}