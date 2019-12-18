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
struct lanai_dev {int conf1; } ;

/* Variables and functions */
 int CONFIG1_POWERDOWN ; 
 int /*<<< orphan*/  conf2_write (struct lanai_dev const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void conf2_write_if_powerup(const struct lanai_dev *lanai)
{
#ifdef USE_POWERDOWN
	if (unlikely((lanai->conf1 & CONFIG1_POWERDOWN) != 0))
		return;
#endif /* USE_POWERDOWN */
	conf2_write(lanai);
}