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

/* Variables and functions */
 int /*<<< orphan*/  txseginfo_zone ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ertt_mod_destroy(void)
{

	uma_zdestroy(txseginfo_zone);

	return (0);
}