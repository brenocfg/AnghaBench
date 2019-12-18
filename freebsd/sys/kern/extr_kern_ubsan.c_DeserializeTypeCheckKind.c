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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t __arraycount (char const**) ; 

__attribute__((used)) static const char *
DeserializeTypeCheckKind(uint8_t hhuTypeCheckKind)
{
	const char *rgczTypeCheckKinds[] = {
		"load of",
		"store to",
		"reference binding to",
		"member access within",
		"member call on",
		"constructor call on",
		"downcast of",
		"downcast of",
		"upcast of",
		"cast to virtual base of",
		"_Nonnull binding to",
		"dynamic operation on"
	};

	ASSERT(__arraycount(rgczTypeCheckKinds) > hhuTypeCheckKind);

	return rgczTypeCheckKinds[hhuTypeCheckKind];
}