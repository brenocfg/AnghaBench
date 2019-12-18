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
 scalar_t__ isdigit (char) ; 
 scalar_t__ islower (char) ; 

__attribute__((used)) static inline u_char
xdtoi(u_char c)
{
	if (isdigit(c))
		return (u_char)(c - '0');
	else if (islower(c))
		return (u_char)(c - 'a' + 10);
	else
		return (u_char)(c - 'A' + 10);
}