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
struct mystate {size_t level; int /*<<< orphan*/ * sbuf; } ;
typedef  char XML_Char ;

/* Variables and functions */
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  sbuf_bcat (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
CharData(void *userData , const XML_Char *s , int len)
{
	struct mystate *mt;
	const char *b, *e;

	mt = userData;

	b = s;
	e = s + len - 1;
	while (isspace(*b) && b < e)
		b++;
	while (isspace(*e) && e > b)
		e--;
	if (e != b || (*b && !isspace(*b)))
		sbuf_bcat(mt->sbuf[mt->level], b, e - b + 1);
}