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
struct charlcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  charlcd_to_priv (struct charlcd*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void charlcd_free(struct charlcd *lcd)
{
	kfree(charlcd_to_priv(lcd));
}