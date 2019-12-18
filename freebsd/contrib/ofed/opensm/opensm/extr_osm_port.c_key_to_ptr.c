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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void *key_to_ptr(uint64_t k)
{
	void *p = 0;

	memcpy(&p, &k, sizeof(void *));
	return p;
}