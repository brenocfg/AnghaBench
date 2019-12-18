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

__attribute__((used)) static int
roff_getop(const char *v, int *pos, char *res)
{

	*res = v[*pos];

	switch (*res) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '&':
	case ':':
		break;
	case '<':
		switch (v[*pos + 1]) {
		case '=':
			*res = 'l';
			(*pos)++;
			break;
		case '>':
			*res = '!';
			(*pos)++;
			break;
		case '?':
			*res = 'i';
			(*pos)++;
			break;
		default:
			break;
		}
		break;
	case '>':
		switch (v[*pos + 1]) {
		case '=':
			*res = 'g';
			(*pos)++;
			break;
		case '?':
			*res = 'a';
			(*pos)++;
			break;
		default:
			break;
		}
		break;
	case '=':
		if ('=' == v[*pos + 1])
			(*pos)++;
		break;
	default:
		return 0;
	}
	(*pos)++;

	return *res;
}