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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 size_t mbstowcs (int /*<<< orphan*/ *,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static wchar_t *
convert_s_to_ws(const char *s)
{
	size_t len;
	wchar_t *ws = NULL;

	if (s != NULL) {
		len = strlen(s) + 1;
		ws = malloc(len * sizeof(wchar_t));
		assert(mbstowcs(ws, s, len) != (size_t)-1);
	}

	return (ws);
}