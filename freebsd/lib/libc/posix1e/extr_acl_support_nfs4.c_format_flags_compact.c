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
typedef  int uint32_t ;
struct flagnames_struct {char letter; int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
format_flags_compact(char *str, size_t size, uint32_t var,
    const struct flagnames_struct *flags)
{
	size_t i;

	for (i = 0; flags[i].letter != '\0'; i++) {
		assert(i < size);
		if ((flags[i].flag & var) == 0)
			str[i] = '-';
		else
			str[i] = flags[i].letter;
	}

	str[i] = '\0';

	return (0);
}