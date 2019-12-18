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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (unsigned char) ; 

__attribute__((used)) static void
html_putchar(char c)
{

	switch (c) {
	case '"':
		printf("&quot;");
		break;
	case '&':
		printf("&amp;");
		break;
	case '>':
		printf("&gt;");
		break;
	case '<':
		printf("&lt;");
		break;
	default:
		putchar((unsigned char)c);
		break;
	}
}