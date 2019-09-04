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
struct strbuf {int dummy; } ;
struct mailinfo {int /*<<< orphan*/ * s_hdr_data; } ;

/* Variables and functions */
 scalar_t__ cmp_header (struct strbuf const*,scalar_t__) ; 
 scalar_t__* header ; 

__attribute__((used)) static int is_inbody_header(const struct mailinfo *mi,
			    const struct strbuf *line)
{
	int i;
	for (i = 0; header[i]; i++)
		if (!mi->s_hdr_data[i] && cmp_header(line, header[i]))
			return 1;
	return 0;
}