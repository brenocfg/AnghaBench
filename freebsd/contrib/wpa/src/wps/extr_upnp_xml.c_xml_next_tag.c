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

/* Variables and functions */
 scalar_t__ isalnum (char const) ; 

int xml_next_tag(const char *in, const char **out,
		 const char **out_tagname, const char **end)
{
	while (*in && *in != '<')
		in++;
	if (*in != '<')
		return 1;
	*out = ++in;
	if (*in == '/')
		in++;
	*out_tagname = in; /* maybe */
	while (isalnum(*in) || *in == '-')
		in++;
	if (*in == ':')
		*out_tagname = ++in;
	while (*in && *in != '>')
		in++;
	if (*in != '>')
		return 1;
	*end = ++in;
	return 0;
}