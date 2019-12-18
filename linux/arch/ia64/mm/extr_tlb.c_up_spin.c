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
struct spinaphore {int /*<<< orphan*/  serve; } ;

/* Variables and functions */
 int /*<<< orphan*/  ia64_fetchadd (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rel ; 

__attribute__((used)) static inline void up_spin(struct spinaphore *ss)
{
	ia64_fetchadd(1, &ss->serve, rel);
}