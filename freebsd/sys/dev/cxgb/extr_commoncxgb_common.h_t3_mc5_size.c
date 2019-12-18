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
struct mc5 {unsigned int tcam_size; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int t3_mc5_size(const struct mc5 *p)
{
	return p->tcam_size;
}