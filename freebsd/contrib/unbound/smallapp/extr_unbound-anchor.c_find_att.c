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
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const XML_Char*
find_att(const XML_Char **atts, const XML_Char* name)
{
	int i;
	for(i=0; atts[i]; i+=2) {
		if(strcasecmp(atts[i], name) == 0)
			return atts[i+1];
	}
	return NULL;
}