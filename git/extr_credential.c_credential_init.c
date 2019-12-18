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
struct TYPE_2__ {int strdup_strings; } ;
struct credential {TYPE_1__ helpers; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct credential*,int /*<<< orphan*/ ,int) ; 

void credential_init(struct credential *c)
{
	memset(c, 0, sizeof(*c));
	c->helpers.strdup_strings = 1;
}