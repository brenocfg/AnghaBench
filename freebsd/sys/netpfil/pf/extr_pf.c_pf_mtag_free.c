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
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pf_mtag_z ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct m_tag*) ; 

__attribute__((used)) static void
pf_mtag_free(struct m_tag *t)
{

	uma_zfree(pf_mtag_z, t);
}