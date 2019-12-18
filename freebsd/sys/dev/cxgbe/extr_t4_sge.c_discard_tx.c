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
struct sge_eq {int flags; } ;

/* Variables and functions */
 int EQ_ENABLED ; 
 int EQ_QFLUSH ; 

__attribute__((used)) static inline int
discard_tx(struct sge_eq *eq)
{

	return ((eq->flags & (EQ_ENABLED | EQ_QFLUSH)) != EQ_ENABLED);
}