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
typedef  char u_char ;

/* Variables and functions */

__attribute__((used)) static u_char
xflip_symbol(u_char symbol)
{
	static const u_char lchars[] = "`'(){}[]\\/<>";
	static const u_char rchars[] = "'`)(}{][/\\><";
	int pos;

	for (pos = 0; lchars[pos] != '\0'; pos++)
		if (lchars[pos] == symbol)
			return rchars[pos];

	return symbol;
}