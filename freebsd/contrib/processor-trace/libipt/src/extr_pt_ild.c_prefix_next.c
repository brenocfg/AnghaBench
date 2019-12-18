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
typedef  scalar_t__ uint8_t ;
struct pt_ild {int dummy; } ;

/* Variables and functions */
 int prefix_decode (struct pt_ild*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int prefix_next(struct pt_ild *ild, uint8_t length, uint8_t rex)
{
	return prefix_decode(ild, length + 1, rex);
}