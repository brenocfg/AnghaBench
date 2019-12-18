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
typedef  int /*<<< orphan*/  _marker ;

/* Variables and functions */
 char* xmemmem (char const*,size_t,char const*,int) ; 

__attribute__((used)) static const char*
_warc_find_eol(const char *buf, size_t bsz)
{
	static const char _marker[] = "\r\n";
	const char *hit = xmemmem(buf, bsz, _marker, sizeof(_marker) - 1U);

	return hit;
}