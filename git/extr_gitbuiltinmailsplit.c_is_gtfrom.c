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
struct strbuf {size_t len; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ starts_with (scalar_t__,char*) ; 
 size_t strlen (char*) ; 
 size_t strspn (scalar_t__,char*) ; 

__attribute__((used)) static int is_gtfrom(const struct strbuf *buf)
{
	size_t min = strlen(">From ");
	size_t ngt;

	if (buf->len < min)
		return 0;

	ngt = strspn(buf->buf, ">");
	return ngt && starts_with(buf->buf + ngt, "From ");
}