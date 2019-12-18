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
DeserializeBuiltinCheckKind(uint8_t hhuBuiltinCheckKind)
{
	const char *rgczBuiltinCheckKinds[] = {
		"ctz()",
		"clz()"
	};

	ASSERT(__arraycount(rgczBuiltinCheckKinds) > hhuBuiltinCheckKind);

	return rgczBuiltinCheckKinds[hhuBuiltinCheckKind];
}