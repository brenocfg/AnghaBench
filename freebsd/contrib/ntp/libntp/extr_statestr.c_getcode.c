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
struct codestring {int code; char const* string1; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static const char *
getcode(
	int				code,
	const struct codestring *	codetab
	)
{
	char *	buf;

	while (codetab->code != -1) {
		if (codetab->code == code)
			return codetab->string1;
		codetab++;
	}

	LIB_GETBUF(buf);
	snprintf(buf, LIB_BUFLENGTH, "%s_%d", codetab->string1, code);

	return buf;
}