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
typedef  int wchar_t ;

/* Variables and functions */

__attribute__((used)) static void setsuffix(wchar_t c, unsigned char *si)
{
	switch (c){
	case L'k':
	case L'K':
		*si = 1;
		break;
	case L'M':
		*si = 2;
		break;
	case L'G':
		*si = 3;
		break;
	case L'T':
		*si = 4;
		break;
	case L'P':
		*si = 5;
		break;
	case L'E':
		*si = 6;
		break;
	case L'Z':
		*si = 7;
		break;
	case L'Y':
		*si = 8;
		break;
	default:
		*si = 0;
	}
}