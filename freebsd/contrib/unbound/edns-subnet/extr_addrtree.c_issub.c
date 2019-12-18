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
typedef  scalar_t__ addrlen_t ;
typedef  int /*<<< orphan*/  addrkey_t ;

/* Variables and functions */
 scalar_t__ bits_common (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int 
issub(const addrkey_t *s1, addrlen_t l1, 
	const addrkey_t *s2, addrlen_t l2,  addrlen_t skip)
{
	return bits_common(s1, l1, s2, l2, skip) == l1;
}