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
struct seqtable {int* chars; int len; } ;

/* Variables and functions */
#define  CS94 132 
#define  CS96 131 
#define  ECMA 130 
#define  INTERM 129 
#define  OECMA 128 
 int /*<<< orphan*/  isecma (char const) ; 
 int /*<<< orphan*/  isinterm (char const) ; 
 int /*<<< orphan*/  strchr (char*,char const) ; 

__attribute__((used)) static int
seqmatch(const char * __restrict s, size_t n,
    const struct seqtable * __restrict sp)
{
	const int *p;

	p = sp->chars;
	while ((size_t)(p - sp->chars) < n && p - sp->chars < sp->len) {
		switch (*p) {
		case ECMA:
			if (!isecma(*s))
				goto terminate;
			break;
		case OECMA:
			if (*s && strchr("@AB", *s))
				break;
			else
				goto terminate;
		case INTERM:
			if (!isinterm(*s))
				goto terminate;
			break;
		case CS94:
			if (*s && strchr("()*+", *s))
				break;
			else
				goto terminate;
		case CS96:
			if (*s && strchr(",-./", *s))
				break;
			else
				goto terminate;
		default:
			if (*s != *p)
				goto terminate;
			break;
		}

		p++;
		s++;
	}

terminate:
	return (p - sp->chars);
}