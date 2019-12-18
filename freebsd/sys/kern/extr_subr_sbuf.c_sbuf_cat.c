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
struct sbuf {scalar_t__ s_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_put_bytes (struct sbuf*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int
sbuf_cat(struct sbuf *s, const char *str)
{
	size_t n;

	n = strlen(str);
	sbuf_put_bytes(s, str, n);
	if (s->s_error != 0)
		return (-1);
	return (0);
}