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
typedef  int /*<<< orphan*/  u8 ;
struct element {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int for_each_element_completed(const struct element *element,
					     const void *data, size_t datalen)
{
	return (const u8 *) element == (const u8 *) data + datalen;
}