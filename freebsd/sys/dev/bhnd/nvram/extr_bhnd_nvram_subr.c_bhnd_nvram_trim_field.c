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
 int /*<<< orphan*/  bhnd_nv_isspace (char const) ; 
 size_t bhnd_nvram_parse_field (char const**,size_t,char) ; 

size_t
bhnd_nvram_trim_field(const char **inp, size_t ilen, char delim)
{
	const char	*sp;
	size_t		 plen;
	
	plen = bhnd_nvram_parse_field(inp, ilen, delim);
	
	/* Trim trailing whitespace */
	sp = *inp;
	while (plen > 0) {
		if (!bhnd_nv_isspace(*(sp + plen - 1)))
			break;
		
		plen--;
	}
	
	return (plen);
}