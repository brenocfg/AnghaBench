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
struct sleepqueue {int /*<<< orphan*/  sq_blocked; } ;
struct pthread {int dummy; } ;

/* Variables and functions */
 struct pthread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct pthread *
_sleepq_first(struct sleepqueue *sq)
{
	return TAILQ_FIRST(&sq->sq_blocked);
}