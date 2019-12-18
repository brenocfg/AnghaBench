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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_be32enc (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_num_732(unsigned char *p, uint32_t value)
{
	archive_be32enc(p, value);
}