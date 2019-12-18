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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_putunqstr (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  isprint (char) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static void
ctl_putrefid(
	const char *	tag,
	u_int32		refid
	)
{
	size_t nc;

	union {
		uint32_t w;
		uint8_t  b[sizeof(uint32_t)];
	} bytes;

	bytes.w = refid;
	for (nc = 0; nc < sizeof(bytes.b) && bytes.b[nc]; ++nc)
		if (  !isprint(bytes.b[nc])
		    || isspace(bytes.b[nc])
		    || bytes.b[nc] == ','  )
			bytes.b[nc] = '.';
	ctl_putunqstr(tag, (const char*)bytes.b, nc);
}